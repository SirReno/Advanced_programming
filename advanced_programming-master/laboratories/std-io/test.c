#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {

  int fd_in;  //Entrada archivo
     int fd_out; //Archivo de salida
     int n;      //entero positivo
     int bytes;

     char buffer[128];

     // Si no hay 4 argumentos, muestra un error.
     if(argc != 4){
         printf("Forma de uso: cifrado numero origen destino \n");
         return 1;
     }

     // Si el entero no es positivo, muestra error.
     if(atoi(argv[1]) <= 0 && (atoi(argv[1]) <=128  )){
         printf("Error: el primer parametro debe ser un numero entero positivo.\n");
         return 2;
     }

     // Revisa la existencia del archivo.
     if((fd_in = open(argv[2], O_RDONLY)) < 0){
         printf("Error: el archivo %s no existe.\n", argv[2]);
         return 3;
     }

     if ( (fd_out = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0){
         printf("El archivo %s no se ha podido crear\n", argv[3]);
         return 4;
     }

     do{
         bytes = read(fd_in,buffer,128);
         if(bytes)
         {
             write(fd_out,buffer,bytes);
         }
     } while(bytes != 0);


     close(fd_in);
     close(fd_out);

     return 0;
 }

}
