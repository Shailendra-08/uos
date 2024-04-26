
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHM_SIZE 1024
#define KEY 12345

// Comparator function for qsort
int cmpfunc(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int shmid;
    int *shm;

  
    // Create the shared memory segment
    shmid = shmget(KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach to the shared memory segment
    shm = (int *) shmat(shmid, NULL, 0);
    if (shm == (int *) -1) {
        perror("shmat");
        exit(1);
    }

    // Fork a child process for input
    pid_t pid_input = fork();

    if (pid_input < 0) {
        perror("fork");
        exit(1);
    } else if (pid_input == 0) {
        // Child process for input
        printf("Enter the number of elements: ");
        int n;
        scanf("%d", &n);

        printf("Enter %d numbers:\n", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &shm[i + 1]); // Offset by 1 to leave space for storing the number of elements
        }
        shm[0] = n; // Store the number of elements at the beginning of shared memory
        exit(0);
    }

    waitpid(pid_input, NULL, 0);

    pid_t pid_sort = fork();

    if (pid_sort < 0) {
        perror("fork");
        exit(1);
    } else if (pid_sort == 0) {
        int n = shm[0];
        qsort(shm + 1, n, sizeof(int), cmpfunc);
        exit(0);
    }

    waitpid(pid_sort, NULL, 0);

    pid_t pid_display = fork();

    if (pid_display < 0) {
        perror("fork");
        exit(1);
    } else if (pid_display == 0) {
        // Child process for display
        int n = shm[0];
        printf("Sorted numbers: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", shm[i + 1]);
        }
        printf("\n");
        exit(0);
    }

    waitpid(pid_display, NULL, 0);

    if (shmdt(shm) == -1) {
        perror("shmdt");
        exit(1);
    }

    return 0;
}
