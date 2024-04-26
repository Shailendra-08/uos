#include<stdio.h>
#include<omp.h>

int main(){

    int thread_number;

    #pragma omp parallel
    {
        #pragma omp master
        {
            thread_number = omp_get_num_threads();
            printf("Total number of thread : %d\n",thread_number);
        }

        int num_thread = omp_get_thread_num();
        printf("Thread : %d\n",num_thread);
    }
    return 0;
}