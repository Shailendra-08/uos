// Write a program to use vfork system call(login name by child and password by parent)


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>


int main(){

    int pid;
    char login[20],password[20];

    pid = vfork();

    if(pid == 0){
        printf("Enter loginID: ");
        scanf("%s",login);
        printf("\n");
        exit(0);
    }
    else if(pid > 0){
        printf("Password :");
        scanf("%s",password);
        printf("\n");

        printf("Login: %s\n",login);
        printf("Password: %s\n",password);
        exit(0);

    }else{
        printf("Error");
        exit(-1);
    }
    



    return 0;
}