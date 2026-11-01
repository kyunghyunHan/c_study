# 과제

- `hw1.c` ~ `hw9.c`: 번호별 과제 풀이
- `device_driver.c`: 가상 장치 드라이버 과제 풀이
- [시스템 실습의 드라이버](../../systems/device_driver/device_driver.c): 루트에 있던 별도 구현

저장소 루트에서 `make hw`로 `hw9.c`를 빌드하고, `make hw-run`으로 실행합니다. 다른 과제는 필요한 소스 파일을 직접 지정해 컴파일합니다.

```sh
cc -std=c11 -Wall -Wextra exercises/homework/hw1.c -o build/hw1
```

일부 과제는 저장소 루트를 기준으로 `sandbox/data.txt`를 읽습니다. 문제에 맞는 입력 데이터로 준비한 뒤 실행합니다.
