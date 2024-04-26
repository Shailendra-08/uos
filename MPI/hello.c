#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

int main(int argc,char ** argv){
    MPI_Init(&argc,&argv);

    int rank;

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    printf("Hello world form process %d\n",rank);
    MPI_Finalize;

    return 0;
}