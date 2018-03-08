/*
  Rodolfo Rincon Muñoz
  A01206310
  ISC
  8/03/2018
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


//nombre del programa
char *cmd0;
//comandos a ejecutar
char *cmd1;
char *cmd2;
char *cmd3;

//numero de argumentos o argc
int num_arguments;

void handler(int signumn) {

  int pid;
  //se hace un fork para poder tener los 3 procesos intanciados y esperando
  //si no solo funcionaria uno de ellos
  if ((pid = fork()) < 0) {
    perror(cmd0);
    exit(-1);
  } else if (pid == 0) {

    switch (signumn) {
      // kill -s 1 <pid_of_program>
      case 1:
        if (num_arguments == 4) {
          execlp(cmd1, cmd1, (char *) 0);
        } else {
          execlp("ls", "ls", (char *) 0);
        }
        break;
      // kill -s 2 <pid_of_program>
      case 2:
        if (num_arguments == 4) {
          execlp(cmd2, cmd2, (char *) 0);
        } else {
          execlp("ps", "ps", (char *) 0);
        }
        break;
      // kill -s 3 <pid_of_program>
      case 3:
        if (num_arguments == 4) {
          execlp(cmd3, cmd3, (char *) 0);
        } else {
          execlp("pwd", "pwd", (char *) 0);
        }
        break;
    }

  } else {
    wait(NULL);
  }
}


int main (int argc, char* argv[]){

  if (argc != 1 && argc != 4) {
 		fprintf(stderr, "Forma de uso: %s orden1 orden2 orden3\n", argv[0]);
   	fprintf(stderr, "Forma de uso: %s\n", argv[0]);
 		return -1;
   }

   //programa
   cmd0 = argv[0];
   //comandos recibidos
   cmd1 = argv[1];
   cmd2 = argv[2];
   cmd3 = argv[3];
   //la razon por la cual se crea una variable global para pasar el numero
   //de argumentos, es porque signal() solo recibe un numero y la funcion,
   //no le puedes pasar argumentos directamente, por eso se toma
   //el workaround de globals
   num_arguments = argc;

   // kill -s SIGKILL pid - Kill the process

   //aqui se instancian los procesos
   signal(1, handler);
   signal(2, handler);
   signal(3, handler);

   //aqui es donde se queda esperando el programa para que se puedan ejecutar las otras cosas

  while (1) {
     printf("PID %i wating for a signal\n", getpid());
     pause();
   }

 return 0;


}
