# Scientific Programming Homework Final
### 20225164 Minjun Jeon

2024년 가을학기 과학계산 Homework.

Buffon's needle problem (SPRNG, Quasi RNG), Probabilistic Diffusion이 포함되어있음.

## Buffon's needle problem (SPRNG)

Buffon's needle problem을 SPRNG rng를 이용해 계산합니다.

l = 0.1인 경우에 대해 계산을 수행함.

### 실행 방법

본 리포지토리의 root를 기준으로, buffon으로 워크스페이스를 옮깁니다. bash 명령어를 기준으로 작성됨.

```
cd buffon
```
make를 이용해 컴파일을 실행합니다.

```
make
```

또는 make clean을 이용해 파일들을 정리할 수 있음.

```
make clean
```

만약 library 관련해서 compile error가 발생하면, Makefile에서 SPRNG include와 library path를 재설정하십시오.


프로그램을 실행하려면, mpirun을 이용하세요.

```
mpirun -np (원하는 개수) ./main
```

실행 결과는 output.txt에 저장됩니다. 본 파일을 통계 분석하려면 python 파일을 실행하세요. pip install은 라이브러리가 미설치된 경우에만 실행하세요.

```
pip install numpy
pip install scipy
pip install matplotlib

python analysis.py
```

그러면 output폴더에 result.png가 저장됩니다.

## Buffon's needle problem (Quasi)

Quasi Random Number (2D Sobol)을 이용한 uniform한 sampling으로 Buffon's needles problem을 계산합니다. scipy의 sobol 구현을 사용함.


### 실행 방법

본 리포지토리의 root를 기준으로, buffonQuasi으로 워크스페이스를 옮깁니다.

```
cd buffonQuasi
```

프로그램을 실행하려면, mpirun을 이용하세요. 시뮬레이션과 통계 분석 코드가 힌 파일에 포함되어있습니다.

```
mpirun -np (원하는 개수) python main.py
```

만약 예기치 못한 오류가 발생하면, python main.py 를 대신 실행하세요.


실행 결과는 output폴더에 result.png가 저장됩니다.

## Probabilistic Diffusion

infinete conductor plane으로부터 1만큼 떨어진 위치에 전하량 1을 띤 point charge가 존재하는 상황에서, isotropic brownian motion을 이용해 induced charge의 분포를 계산합니다. 이론적으로는 분포가 r / (r^2+1)^(3/2)에 비례합니다.

### 실행 방법

본 리포지토리의 root를 기준으로, potential으로 워크스페이스를 옮깁니다.

```
cd potential
```

ake를 이용해 컴파일을 실행합니다.

```
make
```

또는 make clean을 이용해 파일들을 정리할 수 있음.

```
make clean
```

만약 library 관련해서 compile error가 발생하면, Makefile에서 SPRNG include와 library path를 재설정하십시오.


프로그램을 실행하려면, mpirun을 이용하세요.

```
mpirun -np (원하는 개수) ./main
```

실행 결과는 output.txt에 저장됩니다. 본 파일을 통계 분석하려면 python 파일을 실행하세요. pip install은 라이브러리가 미설치된 경우에만 실행하세요.

```
pip install numpy
pip install matplotlib

python analysis.py
```

그러면 output폴더에 result.png가 저장됩니다.