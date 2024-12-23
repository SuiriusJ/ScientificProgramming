#include <iostream>

#include "write_file.h"
#include "mean.h"

#include <mpi.h>
#include <cmath>

#define SIMPLE_SPRNG		/* simple interface                        */
#define USE_MPI			/* use MPI to find number of processes     */
#include "sprng_cpp.h"

#define SEED 985456376

using namespace std;

int main(int argc, char *argv[])
{
    double rn;
    int i, myid ,numprocs;
    int gtype = 0;

    /*************************** MPI, SPRNG 초기화***********************************/
    // Init MPI  
    MPI::Init(argc, argv);

    // Find Process ID
    myid = MPI::COMM_WORLD.Get_rank(); 

    // Find Process Num
    numprocs = MPI::COMM_WORLD.Get_size();

    // Init SPRNG
    init_sprng(SEED,SPRNG_DEFAULT,gtype);

    /*************************** 프로그램 시작 ***********************************/
    cout << "------------- Simulate for l=0.1 case ----------------" << endl;

    // 변수 정의
    double l = 0.1;

    //각 경우에 대해 mpi마다 측정할 샘플의 개수
    int measure_num_per_mpi = 100;

    // n = k * numprocs 일 때 플롯
    int num_case = 6;
    int k[] = {100, 1000, 10000, 100000, 1000000, 10000000};

    // 결과 담을 상자
    double est_pi[] = {0, 0, 0, 0, 0, 0};
    double est_pi_std[] = {0, 0, 0, 0, 0, 0};

    
    // for문 돌려가면서 측정 : k[i_case]번 측정한다고 할떄
    for(int i_case =0 ; i_case < num_case; i_case++){

        // 예측한 파이값 담을 배열
        double *pis = new double[measure_num_per_mpi];



        double *global_array = nullptr;
        if (myid == 0) {
            global_array = new double[measure_num_per_mpi * numprocs]; // 결과를 저장할 배열
        }



        // 여러번 측정, 파이값 예측
        for(int i_m=0; i_m< measure_num_per_mpi; i_m++){
            // 측정값 담을 변수
            int cnt = 0;

            // k[i_case]번 측정
            for(int i=0; i < k[i_case]; i++){
                // 코사인 값
                double _cos = cos(sprng() * M_PI * 0.5);

                // 바늘의 왼쪽 위치
                double _left = sprng() * 0.5 - _cos * 0.5 * l;

                // 바늘이 걸쳤으면 카운트 증가
                if(_left < 0) cnt+= 1;
            }



            //파이값 계산
            pis[i_m] = 2.0 * l * k[i_case] / cnt;
        }

        // 각 프로세스의 배열을 모음
        MPI_Gather(pis, measure_num_per_mpi, MPI::DOUBLE, global_array, measure_num_per_mpi, MPI::DOUBLE, 0, MPI_COMM_WORLD);

        // rank 0에서 pi값 계산
        if(myid == 0){
            est_pi[i_case] = Calc_Mean(global_array, measure_num_per_mpi * numprocs);
            est_pi_std[i_case] = Calc_Std(global_array, measure_num_per_mpi * numprocs);

            cout << "result for n = " << k[i_case] << " : " << est_pi[i_case] << " +/- " << est_pi_std[i_case] << endl;
        }

        // 배열 해제
        delete[] pis;
        if (myid == 0) delete[] global_array;
    }

    // rank 0에서 결과를 파일로 출력
    if(myid == 0){
        const char* filename = "output.txt";
        writeArraysToFile(filename, k, est_pi, est_pi_std, num_case);

        std::cout << "Data written to " << filename << std::endl;
    }

    /*************************** 프로그램 정리 ***********************************/
    // Terminate MPI
    MPI::Finalize();

    return 0;
}



