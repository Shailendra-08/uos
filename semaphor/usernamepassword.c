#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/sem.h>

#define KEY 12345

void f1(int sem_id,char *username)
{
    printf("Enter username: ");
    fflush(stdout);

    // Wait for user input
    scanf("%s", username);

    // Signal that username is entered
    struct sembuf sops = {0, 1, 0};
    semop(sem_id, &sops, 1);
}

// Function f2: Entering password
void f2(int sem_id, char *username, char *password)
{
    // Wait for the semaphore to become positive, indicating that the username is entered
    struct sembuf sops = {0, -1, 0};
    semop(sem_id, &sops, 1);

    // Entering password
    printf("Enter password for user '%s': ", username);
    fflush(stdout);

    // Wait for user input
    scanf("%s", password);
}

int main()
{
    // Create a semaphore set with one semaphore
    int sem_id = semget(KEY, 1, IPC_CREAT | 0666);
    if (sem_id == -1)
    {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    if (semctl(sem_id, 0, SETVAL, 0) == -1)
    {
        perror("semctl");
        exit(0);
    }

    // Variables to hold username and password
    char username[100];
    char password[100];

    // Execute f1
    f1(sem_id, username);

    // Execute f2
    f2(sem_id, username, password);

    // Output username and password
    printf("Username: %s\n", username);
    printf("Password: %s\n", password);

    // Remove the semaphore set
    if (semctl(sem_id, 0, IPC_RMID, 0) == -1)
    {
        exit(0);
    }


    return 0;
}