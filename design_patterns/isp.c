// 학생 인터패이스

#include <stdio.h>

/* ===== 인터페이스 ===== */

// 학생 인터페이스
typedef struct {
    void (*course_registration)(void);
    void (*grade_inquiry)(void);
} StudentInterface;

// 교수 인터페이스
typedef struct {
    void (*grade_entry)(void);
    void (*attendance_inquiry)(void);
} ProfessorInterface;

// 직원 인터페이스
typedef struct {
    void (*set_registration_period)(void);
    void (*set_grade_inquiry_period)(void);
} EmployeeInterface;

/* ===== 학사관리 시스템 ===== */

// 세 인터페이스를 제공하는 학사관리 시스템
typedef struct {
    StudentInterface student;
    ProfessorInterface professor;
    EmployeeInterface employee;
} AcademicManagement;

/* ===== 실제 기능 구현 ===== */

static void course_registration(void)
{
    printf("수강 신청 완료\n");
}

static void grade_inquiry(void)
{
    printf("성적 조회 완료\n");
}

static void grade_entry(void)
{
    printf("성적 등록 완료\n");
}

static void attendance_inquiry(void)
{
    printf("출석부 조회 완료\n");
}

static void set_registration_period(void)
{
    printf("수강 신청 기간 설정 완료\n");
}

static void set_grade_inquiry_period(void)
{
    printf("성적 조회 기간 설정 완료\n");
}

// 실제 함수들을 각 인터페이스에 연결
AcademicManagement academic_management_create(void)
{
    return (AcademicManagement){
        .student = {
            .course_registration = course_registration,
            .grade_inquiry = grade_inquiry,
        },
        .professor = {
            .grade_entry = grade_entry,
            .attendance_inquiry = attendance_inquiry,
        },
        .employee = {
            .set_registration_period = set_registration_period,
            .set_grade_inquiry_period = set_grade_inquiry_period,
        },
    };
}

/* ===== 클라이언트 ===== */

// 학생: 학생 인터페이스에만 의존
void student_execute(const StudentInterface *system)
{
    system->course_registration();
    system->grade_inquiry();
}

// 교수: 교수 인터페이스에만 의존
void professor_execute(const ProfessorInterface *system)
{
    system->grade_entry();
    system->attendance_inquiry();
}

// 직원: 직원 인터페이스에만 의존
void employee_execute(const EmployeeInterface *system)
{
    system->set_registration_period();
    system->set_grade_inquiry_period();
}

int main(void)
{
    AcademicManagement academic = academic_management_create();

    // 각 클라이언트에 필요한 인터페이스만 전달
    student_execute(&academic.student);
    professor_execute(&academic.professor);
    employee_execute(&academic.employee);

    return 0;
}