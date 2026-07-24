#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define INITIAL_ARG_CAPACITY 16
#define TOKEN_BUFFER_SIZE 4096

typedef struct {
    char **argv;
    size_t argc;
    size_t capacity;

    char *input_file;
    char *output_file;

    bool append_output;
    bool background;
} Command;

static volatile sig_atomic_t foreground_pid = -1;

/* --------------------------------------------------
 * 유틸리티
 * -------------------------------------------------- */

static void print_error(const char *message)
{
    fprintf(stderr, "mini-shell: %s\n", message);
}

static void *checked_malloc(size_t size)
{
    void *pointer = malloc(size);

    if (pointer == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    return pointer;
}

static void *checked_realloc(void *pointer, size_t size)
{
    void *new_pointer = realloc(pointer, size);

    if (new_pointer == NULL) {
        perror("realloc");
        free(pointer);
        exit(EXIT_FAILURE);
    }

    return new_pointer;
}

static char *checked_strdup(const char *source)
{
    char *copy = strdup(source);

    if (copy == NULL) {
        perror("strdup");
        exit(EXIT_FAILURE);
    }

    return copy;
}

/* --------------------------------------------------
 * 시그널 처리
 * -------------------------------------------------- */

static void handle_sigint(int signal_number)
{
    (void)signal_number;

    /*
     * 실행 중인 foreground 자식 프로세스가 있으면
     * 해당 프로세스에 SIGINT를 전달합니다.
     */
    if (foreground_pid > 0) {
        kill((pid_t)foreground_pid, SIGINT);
    } else {
        /*
         * 셸 입력 상태에서는 셸을 종료하지 않고
         * 새로운 프롬프트를 표시합니다.
         */
        const char newline = '\n';
        write(STDOUT_FILENO, &newline, 1);
    }
}

static void install_signal_handlers(void)
{
    struct sigaction action;

    memset(&action, 0, sizeof(action));

    action.sa_handler = handle_sigint;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;

    if (sigaction(SIGINT, &action, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    /*
     * Ctrl+\에 의해 셸이 종료되는 것을 방지합니다.
     */
    signal(SIGQUIT, SIG_IGN);
}

/* --------------------------------------------------
 * Command 구조체
 * -------------------------------------------------- */

static void command_init(Command *command)
{
    command->capacity = INITIAL_ARG_CAPACITY;
    command->argc = 0;

    command->argv = checked_malloc(
        command->capacity * sizeof(char *)
    );

    command->argv[0] = NULL;

    command->input_file = NULL;
    command->output_file = NULL;

    command->append_output = false;
    command->background = false;
}

static void command_add_argument(
    Command *command,
    const char *argument
)
{
    /*
     * 마지막 NULL 포인터 공간까지 포함해야 합니다.
     */
    if (command->argc + 2 > command->capacity) {
        command->capacity *= 2;

        command->argv = checked_realloc(
            command->argv,
            command->capacity * sizeof(char *)
        );
    }

    command->argv[command->argc] =
        checked_strdup(argument);

    command->argc++;
    command->argv[command->argc] = NULL;
}

static void command_destroy(Command *command)
{
    for (size_t i = 0; i < command->argc; i++) {
        free(command->argv[i]);
    }

    free(command->argv);
    free(command->input_file);
    free(command->output_file);

    command->argv = NULL;
    command->argc = 0;
    command->capacity = 0;
}

/* --------------------------------------------------
 * 프롬프트
 * -------------------------------------------------- */

static void print_prompt(void)
{
    char current_directory[PATH_MAX];

    if (getcwd(current_directory, sizeof(current_directory)) != NULL) {
        printf("\033[1;32mmini-shell\033[0m:");
        printf("\033[1;34m%s\033[0m$ ", current_directory);
    } else {
        printf("mini-shell$ ");
    }

    fflush(stdout);
}

/* --------------------------------------------------
 * 토크나이저
 * -------------------------------------------------- */

/*
 * 한 개의 토큰을 읽습니다.
 *
 * 지원:
 *   일반 문자열
 *   "double quoted string"
 *   'single quoted string'
 *   backslash escaping
 *   < > >> &
 */
static int read_token(
    const char **cursor,
    char *token,
    size_t token_size
)
{
    const char *current = *cursor;
    size_t position = 0;
    char quote = '\0';

    while (isspace((unsigned char)*current)) {
        current++;
    }

    if (*current == '\0') {
        *cursor = current;
        return 0;
    }

    /*
     * 연산자 토큰 처리
     */
    if (*current == '<' || *current == '&') {
        token[0] = *current;
        token[1] = '\0';

        current++;
        *cursor = current;

        return 1;
    }

    if (*current == '>') {
        token[position++] = *current;
        current++;

        if (*current == '>') {
            token[position++] = *current;
            current++;
        }

        token[position] = '\0';
        *cursor = current;

        return 1;
    }

    while (*current != '\0') {
        char character = *current;

        if (quote == '\0') {
            if (isspace((unsigned char)character)) {
                break;
            }

            if (
                character == '<' ||
                character == '>' ||
                character == '&'
            ) {
                break;
            }

            if (character == '\'' || character == '"') {
                quote = character;
                current++;
                continue;
            }

            if (character == '\\' && current[1] != '\0') {
                current++;
                character = *current;
            }
        } else {
            if (character == quote) {
                quote = '\0';
                current++;
                continue;
            }

            /*
             * 큰따옴표 내부에서는 backslash escape를 허용합니다.
             */
            if (
                quote == '"' &&
                character == '\\' &&
                current[1] != '\0'
            ) {
                current++;
                character = *current;
            }
        }

        if (position + 1 >= token_size) {
            print_error("token is too long");
            return -1;
        }

        token[position++] = character;
        current++;
    }

    if (quote != '\0') {
        print_error("unterminated quote");
        return -1;
    }

    token[position] = '\0';
    *cursor = current;

    return 1;
}

/* --------------------------------------------------
 * 명령어 파싱
 * -------------------------------------------------- */

static int parse_command(
    const char *line,
    Command *command
)
{
    const char *cursor = line;
    char token[TOKEN_BUFFER_SIZE];

    enum {
        EXPECT_NORMAL,
        EXPECT_INPUT_FILE,
        EXPECT_OUTPUT_FILE,
        EXPECT_APPEND_FILE
    } state = EXPECT_NORMAL;

    while (true) {
        int result = read_token(
            &cursor,
            token,
            sizeof(token)
        );

        if (result < 0) {
            return -1;
        }

        if (result == 0) {
            break;
        }

        if (state == EXPECT_INPUT_FILE) {
            free(command->input_file);
            command->input_file = checked_strdup(token);
            state = EXPECT_NORMAL;
            continue;
        }

        if (
            state == EXPECT_OUTPUT_FILE ||
            state == EXPECT_APPEND_FILE
        ) {
            free(command->output_file);
            command->output_file = checked_strdup(token);

            command->append_output =
                state == EXPECT_APPEND_FILE;

            state = EXPECT_NORMAL;
            continue;
        }

        if (strcmp(token, "<") == 0) {
            state = EXPECT_INPUT_FILE;
            continue;
        }

        if (strcmp(token, ">") == 0) {
            state = EXPECT_OUTPUT_FILE;
            continue;
        }

        if (strcmp(token, ">>") == 0) {
            state = EXPECT_APPEND_FILE;
            continue;
        }

        if (strcmp(token, "&") == 0) {
            command->background = true;

            /*
             * & 뒤에는 다른 인자를 허용하지 않습니다.
             */
            const char *remaining = cursor;

            while (isspace((unsigned char)*remaining)) {
                remaining++;
            }

            if (*remaining != '\0') {
                print_error(
                    "'&' must appear at the end of a command"
                );

                return -1;
            }

            break;
        }

        command_add_argument(command, token);
    }

    if (state != EXPECT_NORMAL) {
        print_error("missing file after redirection operator");
        return -1;
    }

    return 0;
}

/* --------------------------------------------------
 * 리다이렉션
 * -------------------------------------------------- */

static int apply_redirections(const Command *command)
{
    if (command->input_file != NULL) {
        int input_fd = open(
            command->input_file,
            O_RDONLY
        );

        if (input_fd == -1) {
            perror(command->input_file);
            return -1;
        }

        if (dup2(input_fd, STDIN_FILENO) == -1) {
            perror("dup2 input");
            close(input_fd);
            return -1;
        }

        close(input_fd);
    }

    if (command->output_file != NULL) {
        int flags = O_WRONLY | O_CREAT;

        if (command->append_output) {
            flags |= O_APPEND;
        } else {
            flags |= O_TRUNC;
        }

        int output_fd = open(
            command->output_file,
            flags,
            0644
        );

        if (output_fd == -1) {
            perror(command->output_file);
            return -1;
        }

        if (dup2(output_fd, STDOUT_FILENO) == -1) {
            perror("dup2 output");
            close(output_fd);
            return -1;
        }

        close(output_fd);
    }

    return 0;
}

/* --------------------------------------------------
 * Built-in 명령어
 * -------------------------------------------------- */

static int builtin_cd(const Command *command)
{
    const char *target_directory;

    if (command->argc >= 2) {
        target_directory = command->argv[1];
    } else {
        target_directory = getenv("HOME");

        if (target_directory == NULL) {
            print_error("HOME environment variable is not set");
            return 1;
        }
    }

    if (command->argc > 2) {
        print_error("cd: too many arguments");
        return 1;
    }

    if (chdir(target_directory) == -1) {
        perror("cd");
        return 1;
    }

    return 0;
}

static int builtin_pwd(const Command *command)
{
    (void)command;

    char current_directory[PATH_MAX];

    if (getcwd(current_directory, sizeof(current_directory)) == NULL) {
        perror("pwd");
        return 1;
    }

    puts(current_directory);

    return 0;
}

static int builtin_help(const Command *command)
{
    (void)command;

    puts("Mini Shell");
    puts("");
    puts("Built-in commands:");
    puts("  cd [directory]   Change current directory");
    puts("  pwd              Print current directory");
    puts("  help             Show this help");
    puts("  exit [status]    Exit the shell");
    puts("");
    puts("Supported syntax:");
    puts("  command arg1 arg2");
    puts("  command > output.txt");
    puts("  command >> output.txt");
    puts("  command < input.txt");
    puts("  command &");
    puts("  echo \"hello world\"");

    return 0;
}

static int parse_exit_status(const char *value, int *status)
{
    char *end_pointer = NULL;
    errno = 0;

    long parsed = strtol(
        value,
        &end_pointer,
        10
    );

    if (
        errno != 0 ||
        end_pointer == value ||
        *end_pointer != '\0'
    ) {
        return -1;
    }

    *status = (unsigned char)parsed;

    return 0;
}

/*
 * 반환값:
 *   0 = 셸 계속 실행
 *   1 = 셸 종료
 */
static int builtin_exit(
    const Command *command,
    int *exit_status
)
{
    if (command->argc > 2) {
        print_error("exit: too many arguments");
        return 0;
    }

    if (command->argc == 2) {
        if (
            parse_exit_status(
                command->argv[1],
                exit_status
            ) == -1
        ) {
            print_error("exit: numeric argument required");
            *exit_status = 2;
        }
    }

    return 1;
}

static bool is_builtin(const Command *command)
{
    if (command->argc == 0) {
        return false;
    }

    const char *name = command->argv[0];

    return
        strcmp(name, "cd") == 0 ||
        strcmp(name, "pwd") == 0 ||
        strcmp(name, "help") == 0 ||
        strcmp(name, "exit") == 0;
}

static int execute_builtin(
    const Command *command,
    int *should_exit,
    int *exit_status
)
{
    const char *name = command->argv[0];

    if (strcmp(name, "cd") == 0) {
        return builtin_cd(command);
    }

    if (strcmp(name, "pwd") == 0) {
        return builtin_pwd(command);
    }

    if (strcmp(name, "help") == 0) {
        return builtin_help(command);
    }

    if (strcmp(name, "exit") == 0) {
        *should_exit = builtin_exit(
            command,
            exit_status
        );

        return 0;
    }

    return 1;
}

/* --------------------------------------------------
 * 외부 프로그램 실행
 * -------------------------------------------------- */

static int execute_external(const Command *command)
{
    pid_t process_id = fork();

    if (process_id == -1) {
        perror("fork");
        return 1;
    }

    if (process_id == 0) {
        /*
         * 자식 프로세스는 기본 SIGINT 동작을 사용합니다.
         */
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);

        if (apply_redirections(command) == -1) {
            _exit(126);
        }

        execvp(command->argv[0], command->argv);

        /*
         * execvp가 반환했다면 실행 실패입니다.
         */
        fprintf(
            stderr,
            "mini-shell: %s: %s\n",
            command->argv[0],
            strerror(errno)
        );

        if (errno == ENOENT) {
            _exit(127);
        }

        _exit(126);
    }

    if (command->background) {
        printf("[background pid %d]\n", process_id);
        return 0;
    }

    foreground_pid = process_id;

    int status;

    while (waitpid(process_id, &status, WUNTRACED) == -1) {
        if (errno == EINTR) {
            continue;
        }

        perror("waitpid");
        foreground_pid = -1;
        return 1;
    }

    foreground_pid = -1;

    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }

    if (WIFSIGNALED(status)) {
        int signal_number = WTERMSIG(status);

        fprintf(
            stderr,
            "terminated by signal %d\n",
            signal_number
        );

        return 128 + signal_number;
    }

    return 1;
}

/* --------------------------------------------------
 * 종료된 백그라운드 프로세스 정리
 * -------------------------------------------------- */

static void reap_background_processes(void)
{
    int status;
    pid_t process_id;

    while (
        (process_id = waitpid(-1, &status, WNOHANG)) > 0
    ) {
        if (WIFEXITED(status)) {
            printf(
                "[background pid %d exited with status %d]\n",
                process_id,
                WEXITSTATUS(status)
            );
        } else if (WIFSIGNALED(status)) {
            printf(
                "[background pid %d terminated by signal %d]\n",
                process_id,
                WTERMSIG(status)
            );
        }
    }
}

/* --------------------------------------------------
 * 메인
 * -------------------------------------------------- */

int main(void)
{
    char *line = NULL;
    size_t line_capacity = 0;

    int exit_status = 0;
    int should_exit = 0;

    install_signal_handlers();

    while (!should_exit) {
        reap_background_processes();
        print_prompt();

        errno = 0;

        ssize_t line_length = getline(
            &line,
            &line_capacity,
            stdin
        );

        if (line_length == -1) {
            if (feof(stdin)) {
                putchar('\n');
                break;
            }

            if (errno == EINTR) {
                clearerr(stdin);
                continue;
            }

            perror("getline");
            exit_status = 1;
            break;
        }

        /*
         * 마지막 줄바꿈 제거
         */
        if (
            line_length > 0 &&
            line[line_length - 1] == '\n'
        ) {
            line[line_length - 1] = '\0';
        }

        Command command;
        command_init(&command);

        if (parse_command(line, &command) == -1) {
            command_destroy(&command);
            continue;
        }

        if (command.argc == 0) {
            command_destroy(&command);
            continue;
        }

        /*
         * cd와 exit는 부모 셸 프로세스에서 실행해야 합니다.
         *
         * 자식에서 cd를 실행하면 자식 프로세스의 디렉터리만
         * 변경되기 때문에 셸의 현재 디렉터리는 바뀌지 않습니다.
         */
        if (is_builtin(&command)) {
            if (
                command.input_file != NULL ||
                command.output_file != NULL
            ) {
                print_error(
                    "redirection for built-in commands "
                    "is not implemented"
                );
            } else {
                execute_builtin(
                    &command,
                    &should_exit,
                    &exit_status
                );
            }
        } else {
            execute_external(&command);
        }

        command_destroy(&command);
    }

    free(line);

    return exit_status;
}