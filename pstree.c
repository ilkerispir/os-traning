#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int leaf_node() {
    char file_name[20];
    sprintf(file_name, "%d.txt", getpid());
    FILE *fp = fopen(file_name, "w");
    srand(getpid());
    fprintf(fp, "%d", (rand() % 100));
    fclose(fp);
}

int parent(int pid1, int pid2) {
    wait(NULL);
    char file_name1[20];
    sprintf(file_name1, "%d.txt", pid1);
    char file_name2[20];
    sprintf(file_name2, "%d.txt", pid2);
    char file_name3[20];
    sprintf(file_name3, "%d.txt", getpid());

    FILE *fp1, *fp2, *fp3;
    fp1 = fopen(file_name1, "r");
    fp2 = fopen(file_name2, "r");

    int left, right;
    fscanf(fp1, "%d", &left);
    fscanf(fp2, "%d", &right);
    fclose(fp1);
    fclose(fp2);

    fp3 = fopen(file_name3, "w");
    fprintf(fp3, "%d", left+right);
    fclose(fp3);
}

void create_tree(int height){
    if(height == 0) {
        leaf_node();
        return;
    }

    int pid = fork();

    if(pid > 0) {
        int pid2 = fork();
        if(pid2 > 0) {
            //parent
            wait(NULL);
            printf("parent: %d, c1: %d, c2: %d\n", getpid(), pid, pid2);
            fflush(stdout);
            parent(pid, pid2);
        } else if(pid2 == 0) {
            //left child
            create_tree(--height); 
        }
    } else if(pid == 0) {
        //right child
        create_tree(--height);
    }
}

int main(){
    create_tree(3);
}