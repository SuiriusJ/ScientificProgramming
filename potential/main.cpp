#include <iostream>

#include "WOS.h"
#include "write_file.h"

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

    if(myid == 0) cout << "도선 평면으로부터 1C 전하가 1m 떨어져있을 때, induced charge의 분포를 계산합니다." << endl;

    // 각종변수 설정

    // tolerance 값
    double epsilon = 0.05;

    // 확산시킬 점의 개수
    long num_per_mpi = 100000000;

    // 최대 이동수
    int max_move = 1000;

    // bin의 개수
    int num_bin = 1000;
    double r_max = 100;

    // bin
    int *r_bin = new int[num_bin];
    std::fill(r_bin, r_bin + num_bin, 0);

    // global bin
    int *r_bin_global = nullptr;
    if(myid == 0){
        r_bin_global = new int[num_bin];
    }

    for(long i=0; i< num_per_mpi; i++){
        // 초기 좌표 설정
        double x = 0;
        double y = 0;
        double z = 1;

        for(int j=0; j< max_move; j++){
            //반지름을 z값으로 설정한 구 껍질에서 이동
            double theta = sample_theta(sprng());
            double phi = sample_phi(sprng());
            

            x += z * sin(theta) * cos(phi);
            y += z * sin(theta) * sin(phi);
            z += z * cos(theta);

            //만약 경계를 건드리면
            if(z<epsilon){
                //r값 계산
                double r = sqrt(x*x + y*y);

                // bin 범위 초과면 버리기
                if(r > r_max) continue;

                //빈 인덱스 계산
                int idx = r * (num_bin-1) / r_max;
                //bin에 집어넣기
                r_bin[idx] += 1;

                break;
            }
        }   
    }

    //취합하기
    MPI_Reduce(r_bin, r_bin_global, num_bin, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(myid == 0){
        //결과 파일로 출력하기
        const char* filename = "output.txt";
        writeArraysToFile(filename, r_bin_global, num_bin);

        std::cout << "Data written to " << filename << std::endl;
    }



    /*************************** 프로그램 정리 ***********************************/
    delete[] r_bin;
    if(myid==0) delete[] r_bin_global;
    
    // Terminate MPI
    MPI::Finalize();

    return 0;
}