#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int pid;
    pid = fork();

    if(pid > 0)
    {
        //parrent
        wait(NULL); //first child process will run
        printf("parrent: %d, my pid: %d\n", pid, getpid());
    } else if(pid == 0){
        //child
        printf("child: %d, my pid: %d\n", pid, getpid());
    } else {
        //error
    }
}