#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void create_child(int i, int level, char* program);

void create_process(int i, int level, char* program){
    int pid, j;

    if((pid=fork()) < 0 ){
        perror(program);
        exit(-1);
    }else if(pid == 0){
        i++;
        create_child(i, level, program);
    }else{
        for(j = 0 ; j < i ; j++ ){
            printf("\t");
        }
        printf("PPID = %i PID = %i LEVEL = %i\n", getppid(), getppid(), i);
        wait(NULL);
        exit(0);
    }
}

void create_child(int i, int level, char*program){
    int pid, j;

    if(i==0){
        create_process(i, level, program);
    }else if(i != (level +1)){
        for(j=0; j< i; j++){
            create_process(i,level,program);
        }
    }
}

int main (int argc, char* argv[]){
    int level, i=0;

    //validacion de cantidad de argumentos
    if(argc != 2){
        fprintf(stderr, "Forma de usa: %snum\n",argv[0]);
        return -1;
    }


    //validacion de segundo argumento.
    level = atoi(argv[1]);
    if(level<= 0){
        fprintf(stderr, "Error: el programa recibe un numero entero positivo mayor a 0\n");
        return -1;
    }

    create_process(i, level, argv[0]);

    return 0;
}h
