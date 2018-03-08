#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {

  int file_input;
  int file_output;

  int shift;
  int string_bytes;

  char shifting[128];
  char file_string[128];

  if(argc == 4){
    if(atoi(argv[1]) >0 && (atoi(argv[1])<128)) {
      if((file_input=open(argv[2], O_RDONLY)) >= 0){
        if((file_output=open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0666))>=0){
          shift=atoi(argv[1]);

          while((string_bytes=read(file_input, file_string, sizeof(char)*128))==128){
            for(int i=0; i<string_bytes-shift; i++){
              shifting[i]=file_string[i+shift];
            }

            for(int i=string_bytes-shift; i<string_bytes; i++){
              shifting[i]=file_string[i-(128-shift)];
            }

            write(file_output,&shifting,string_bytes);

          }

          close(file_input);
          close(file_output);
          printf("Shift done\n");
          return 0;
        }else{
          printf("El archvo %s  no se ha podido crear, talves no tengas permisos\n", argv[3]);
          return 4;
        }
      }else{
          printf("El archivo %s no existe. \n", argv[2]);
          return 3;
      }
    }else{
      printf("El primer parametro debe ser un entero positivo mayor que 0 y menor que 128\n");
      return 2;
    }
  }else{
    printf("Forma de uso: cifrado numero origen destino\n Faltan parametros\n");
    return 1;
  }

}
