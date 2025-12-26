# minishell

C로 작성된 최소한의 Unix 셸 구현체로, bash/zsh의 기본 기능을 재현합니다.

## 📋 목차

- [개요](#개요)
- [주요 기능](#주요-기능)
- [빌드 방법](#빌드-방법)
- [사용법](#사용법)
- [내장 명령어](#내장-명령어)
- [지원 기능](#지원-기능)
- [프로젝트 구조](#프로젝트-구조)
- [개발 워크플로우](#개발-워크플로우)

## 개요

Minishell은 명령어 실행, 파이핑, 리다이렉션, 환경 변수 관리, 시그널 처리 등 핵심 셸 기능을 제공하는 간소화된 셸 구현체입니다. 셸이 저수준에서 어떻게 동작하는지 이해하기 위한 교육용 프로젝트입니다.

## 주요 기능

- ✅ **명령어 실행**: 내장 명령어와 외부 명령어 실행
- ✅ **파이핑**: 파이프(`|`)를 사용한 명령어 체이닝
- ✅ **리다이렉션**: 입력(`<`) 및 출력(`>`, `>>`) 리다이렉션
- ✅ **환경 변수**: 환경 변수 관리 및 확장 (`$VAR`)
- ✅ **따옴표 처리**: 작은따옴표, 큰따옴표, 이스케이프 시퀀스 지원
- ✅ **시그널 처리**: `SIGINT` (Ctrl+C) 및 `SIGQUIT` (Ctrl+\) 적절한 처리
- ✅ **명령어 구분**: 세미콜론(`;`)을 사용한 명령어 분리 지원
- ✅ **에러 처리**: 포괄적인 에러 메시지 및 종료 코드

## 빌드 방법

### 사전 요구사항

- GCC 컴파일러
- Make
- Unix 계열 운영체제 (macOS, Linux)

### 컴파일

```bash
# 저장소 클론
git clone [remote repository URL]

# 프로젝트 디렉토리로 이동
cd minishell

# 프로젝트 빌드
make

# minishell 실행
./minishell
```

### Makefile 타겟

- `make` 또는 `make all`: 프로젝트 컴파일
- `make clean`: 오브젝트 파일 제거
- `make fclean`: 오브젝트 파일 및 실행 파일 제거
- `make re`: 프로젝트를 처음부터 다시 빌드

## 사용법

컴파일 후 `./minishell`을 실행하여 셸을 시작합니다. 다음과 같은 프롬프트가 표시됩니다:

```
MINISHELL$
```

이제 일반 셸처럼 명령어를 입력할 수 있습니다:

```bash
MINISHELL$ ls -la
MINISHELL$ echo "Hello, World!"
MINISHELL$ pwd
MINISHELL$ cd /path/to/directory
MINISHELL$ exit
```

## 내장 명령어

다음 명령어들은 내장 명령어로 구현되어 있습니다 (셸에서 직접 실행):

| 명령어   | 설명                    | 예제                  |
| -------- | ----------------------- | --------------------- |
| `echo`   | 인자를 stdout에 출력    | `echo hello world`    |
| `cd`     | 디렉토리 변경           | `cd /home/user`       |
| `pwd`    | 현재 작업 디렉토리 출력 | `pwd`                 |
| `export` | 환경 변수 설정          | `export VAR=value`    |
| `unset`  | 환경 변수 제거          | `unset VAR`           |
| `env`    | 환경 변수 목록 표시     | `env`                 |
| `exit`   | 셸 종료                 | `exit` 또는 `exit 42` |

## 지원 기능

### 파이핑

여러 명령어를 연결하여 실행:

```bash
MINISHELL$ ls | grep .c
MINISHELL$ cat file.txt | wc -l
MINISHELL$ echo "hello" | cat
```

### 리다이렉션

**입력 리다이렉션 (`<`):**

```bash
MINISHELL$ cat < file.txt
```

**출력 리다이렉션 (`>` 및 `>>`):**

```bash
MINISHELL$ echo "hello" > output.txt
MINISHELL$ echo "world" >> output.txt
```

### 환경 변수

`$VAR`를 사용하여 환경 변수 확장:

```bash
MINISHELL$ echo $HOME
MINISHELL$ export MY_VAR=test
MINISHELL$ echo $MY_VAR
```

### 따옴표 처리

- **작은따옴표**: 리터럴 내용 보존
- **큰따옴표**: 변수 확장 허용
- **이스케이프 시퀀스**: 백슬래시(`\`)를 사용하여 특수 문자 이스케이프

### 명령어 구분

한 줄에 여러 명령어 실행:

```bash
MINISHELL$ ls; pwd; echo done
```

### 시그널 처리

- **Ctrl+C** (`SIGINT`): 현재 명령어를 중단하거나 프롬프트로 돌아감
- **Ctrl+\\** (`SIGQUIT`): 현재 명령어 종료 (실행 중인 경우)

## 프로젝트 구조

```
minishell/
├── includes/
│   ├── minishell.h      # 함수 선언이 포함된 메인 헤더 파일
│   └── struct.h         # 데이터 구조 정의
├── srcs/
│   ├── main.c           # 진입점 및 메인 루프
│   ├── lexer_1.c        # 토큰화 (렉싱)
│   ├── lexer_2.c        # 렉서 헬퍼 함수
│   ├── parser_1.c       # 명령어 파싱
│   ├── init_cmd.c       # 명령어 리스트 초기화
│   ├── exec_command.c   # 명령어 실행 로직
│   ├── exec_*.c         # 내장 명령어 구현
│   ├── pipe.c           # 파이프 구현
│   ├── redirection.c    # I/O 리다이렉션
│   ├── dollar_quotes.c  # 변수 확장 및 따옴표 처리
│   ├── lst_*.c          # 연결 리스트 연산
│   ├── free_*.c         # 메모리 관리
│   └── error_*.c        # 에러 처리
├── lib/
│   └── libft/           # 커스텀 C 라이브러리 (문자열, 메모리 함수)
├── Makefile             # 빌드 설정
└── README.md            # 이 파일
```

### 주요 데이터 구조

- **`t_minish`**: 메인 셸 상태 (명령어, 환경 변수, 토큰)
- **`t_cmd`**: 명령어 구조 (인자, 파이프, 리다이렉션)
- **`t_env`**: 환경 변수 연결 리스트
- **`t_rdir`**: 리다이렉션 정보 (파일, 파일 디스크립터, 타입)

## 개발 워크플로우

### 1. 저장소 클론

```bash
git clone [remote repository URL]
```

### 2. 새 브랜치 생성

```bash
# 새 브랜치 생성 및 전환
git checkout -b [branch_name]

# 또는 두 단계로 수행
git branch [branch_name]
git checkout [branch_name]
```

### 3. 변경사항 커밋

```bash
# 모든 변경사항 스테이징
git add -A

# 설명이 포함된 커밋 메시지와 함께 커밋
git commit -m "[commit_message]"

# 원격 저장소에 푸시
git push -u origin [branch_name]
```

### 4. Pull Request 생성

GitHub에서 코드 리뷰를 위한 Pull Request를 생성합니다.

### 5. 메인 브랜치와 동기화

변경사항이 병합된 후:

```bash
git checkout master
git pull origin master
```

## 참고 자료

### 리다이렉션과 파이프

1. [셸 리다이렉션 마스터하기](https://putaindecode.io/articles/maitriser-les-redirections-shell/)
2. [dup2() 예제](http://www.cs.loyola.edu/~jglenn/702/S2005/Examples/dup2.html)

## 기술적 세부사항

- **언어**: C
- **표준**: C99
- **컴파일 플래그**: `-Wall -Wextra -Werror`
- **메모리 관리**: 수동 할당/해제
- **프로세스 관리**: `fork()`, `execve()`, `wait()`, `waitpid()`
- **파일 디스크립터**: `dup()`, `dup2()`, `pipe()`, `open()`, `close()`
- **시그널**: `signal()`, `SIGINT`, `SIGQUIT`

## 참고사항

- 이 프로젝트는 교육용 프로젝트이며, 프로덕션 셸이 처리하는 모든 엣지 케이스를 처리하지 못할 수 있습니다
- 일부 고급 셸 기능(작업 제어, 히스토리, 탭 완성 등)은 구현되지 않았습니다
- 셸은 문자열 및 메모리 연산을 위해 커스텀 `libft` 라이브러리를 사용합니다

---

**작성자**: wpark, froussel  
**프로젝트**: 42 School minishell 프로젝트
