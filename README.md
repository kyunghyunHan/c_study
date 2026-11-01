# c_study

C/C++ 문법, 자료구조, 알고리즘, 디자인 패턴, 시스템 프로그래밍을 주제별로 정리한 학습 저장소입니다.

## 폴더 안내

```text
c_study/
├── fundamentals/                 # C 기초 학습과 문서
│   ├── c_language.md             # 문법·포인터·메모리 핵심 정리
│   ├── c100/                     # C 기초 문제
│   ├── cp/                       # 일차별 수업과 포인터 학습 문서
│   ├── bit/                      # 비트 연산과 레지스터 연습
│   ├── deep/                     # 메모리 심화
│   └── malloc/                   # 동적 메모리
├── algorithms/                   # 주제별 알고리즘과 자료구조
│   ├── data_structures/          # 리스트·스택·큐·트리·힙
│   ├── hash_table/               # 해시 테이블 별도 연습
│   ├── search/                   # 순차·이진 탐색
│   ├── sort/                     # 버블·삽입·퀵 정렬
│   ├── graphs/                   # 그래프·위상 정렬·MST·최단 경로
│   ├── bfs/                      # 너비 우선 탐색
│   ├── dfs/                      # 깊이 우선 탐색
│   ├── backtracking/             # 백트래킹
│   ├── brute_force/              # 완전 탐색
│   ├── divide_and_conquer/       # 분할 정복
│   ├── dynamic/                  # 동적 계획법
│   └── greedy/                   # 탐욕 알고리즘
├── exercises/                    # 출처별 문제 풀이와 과제
│   ├── book/                     # 교재 연습
│   ├── homework/                 # 과제와 과제 안내
│   ├── jungol/                   # 정올 문제
│   ├── problem/                  # 수업 문제
│   └── testcase/                 # 개별 연습 문제
├── design_patterns/              # 디자인 원칙과 패턴
│   └── sort_strategy/            # 정렬 정책과 팩토리
│       ├── c/                    # C의 함수 포인터 구현
│       ├── cpp/                  # std::list 기반 C++ 구현
│       └── cpp_owned/            # 스마트 포인터로 정책을 소유하는 구현
├── projects/                     # 연락처·정렬·게임 등 미니 프로젝트
├── systems/                      # 시스템 프로그래밍
│   ├── device_driver/            # 가상 장치 드라이버
│   ├── kernel/                   # 커널 실습
│   ├── kernel201/                # 키보드 입력을 포함한 커널 실습
│   └── network/                  # TCP 네트워크 실습
├── multimedia/ffmpeg/            # FFmpeg 실습
├── sandbox/                      # 임시 실험과 로컬 입력 데이터
└── build/                        # 실행 파일과 디버그 심볼 (Git 제외)
```

## 학습 문서

- [C 언어 핵심 정리](fundamentals/c_language.md)
- [Day 01~09 포인터 정리](fundamentals/cp/POINTER_STUDY_DAY01_DAY09.md)
- [자료구조 구현 목록](algorithms/data_structures/README.md)
- [과제 안내](exercises/homework/README.md)

설명 문서는 관련 소스 폴더에 둡니다. 루트의 README는 전체 구조와 실행 방법을 안내합니다.

## 빌드와 실행

저장소 루트에서 실행합니다. 각 예제는 독립 프로그램이므로 전체 소스를 한꺼번에 링크하지 않습니다.

```sh
make help
make test-run        # C 정렬 정책 예제
make sort-cpp-run    # C++ 정렬 정책 예제
make sort-owned-run  # 스마트 포인터를 사용하는 C++ 예제
make graph-run       # 그래프 예제
make bit-run         # 비트 연산 예제
make hw-run          # hw9 과제
make driver-run      # 가상 장치 드라이버
```

실행 파일은 `build/<대상 이름>`에 생성합니다. `make clean`은 Makefile이 만드는 실행 파일을 정리합니다. C++ 예제에는 C++14 이상을 사용합니다.

일부 예제는 작성 중이라 단독 빌드가 실패할 수 있습니다. 정리 전부터 `dll`, `sq`, `pq`에는 선언·반환형 오류가 있습니다. `hw`는 실제 존재하는 `hw9.c`를 빌드하도록 연결했습니다.

일부 문제 풀이는 `sandbox/data.txt`를 입력으로 사용합니다. 이 파일은 문제마다 내용이 다른 로컬 작업용 데이터이며, 기존처럼 Git에서 제외합니다. 예제에서 요구하는 다른 `.txt` 입력 파일도 별도로 준비해야 합니다.

## 기존 위치 찾기

| 이전 위치 | 현재 위치 |
|---|---|
| `acadamy/{c100,cp,deep,malloc,bit}/` | `fundamentals/` 아래 같은 이름의 폴더 |
| `acadamy/{jungol,problem}/` | `exercises/` 아래 같은 이름의 폴더 |
| `book/`, `homework/`, `testcase/` | `exercises/` 아래 같은 이름의 폴더 |
| `bit/` | `fundamentals/bit/` |
| `algorithms/struct/` | `algorithms/data_structures/` |
| `algorithms/Graph/` | `algorithms/graphs/` |
| `algorithms/Conquer/` | `algorithms/divide_and_conquer/` |
| `algorithms/backtraking/`, `algorithms/greed/`, `algorithms/hashtable/` | `algorithms/backtracking/`, `algorithms/greedy/`, `algorithms/hash_table/` |
| `search/binary_search.c` | `algorithms/search/binary_search_basic.c` |
| `design_pattern/` | `design_patterns/` |
| 루트 `test.c` | `design_patterns/sort_strategy/c/main.c` |
| 루트 `test.cpp`, 정렬 관련 `.cpp`·`.h` | `design_patterns/sort_strategy/cpp/` |
| 루트 `test2.cpp` | `design_patterns/sort_strategy/cpp_owned/main.cpp` |
| 루트 `device_driver.c` | `systems/device_driver/device_driver.c` |
| 루트 `data_struct.md` | `algorithms/data_structures/README.md` |
| 루트 `data.txt` | `sandbox/data.txt` |
| `sandbox/utill.h` | `fundamentals/bit/util.h` |
| 루트 `test`, `test2`, `test.dSYM/` | `build/legacy/` (기존 결과물 보관) |
