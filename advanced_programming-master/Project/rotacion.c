//Rodolfo Rincon
//A01206310
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void rotation(char* directory, char* name, char* program, int number) {
	FILE *file;
	FILE *new_file;
  FILE *last_file;
	char filename[NAME_MAX + 1], new_filename[NAME_MAX + 1],last_log[NAME_MAX+1], character;

  //último archivo
  sprintf(last_log,"%s/%s.%i", directory,name, number--);
  last_file= fopen(last_log, "r");

  if(last_file!=NULL){
    fclose(last_file);
    remove(last_log);
  }else{
    while(last_file==NULL && number > 0 ){
      if(last_file!=NULL){
        fclose(last_file);
      }
      sprintf(last_log,"%s/%s.%i",directory,name, number--);
      last_file=fopen(last_log,"r");
    }

    if(number!=0){
      fclose(last_file);
    }
  }

  for(number; number>=0;number--){

    if(number==0){
      sprintf(filename,"%s/%s.log",directory,name);
    }else{
      sprintf(filename,"%s/%s.log",directory,name,number);
    }

    sprintf(new_filename, "%s/%s.%i", directory,name,number+1);

    file=fopen(filename,"r");
    new_file=fopen(new_filename,"w");

    if(file==NULL){
      perror(program);
      exit(-1);
    }

    if(new_file==NULL){
      perror(program);
      exit(-1);
    }

    while(fscanf(file, "c", &character)!=EOF){
      fprintf(new_file,"%c", character);
    }
    fclose(file);
    fclose(new_file);
    remove(filename);
  }

  sprintf(filename, "%s/%s.log",directory, name);

}

void open_directory(char* directory, char* program, char* l, int time_input, int number) {
	DIR *dir;
	struct dirent *dir_entry;
	char filename[NAME_MAX + 1];
	int exists = 0;

  //validar directorio
	if( (dir = opendir(directory)) == NULL) {
		perror(program);
		exit(-1);
	}

  //validar/buscar un archivo con el nombre, para saber si existe y trabajar en base a ese
	sprintf(filename, "%s.log", l);
	while ( (dir_entry = readdir(dir)) != NULL) {
		if (strcmp(dir_entry->d_name, ".") == 0 ||
			strcmp(dir_entry->d_name, "..")  == 0)
			continue;

		if (strcmp(dir_entry->d_name, filename) == 0) exists = 1;
	}

	if (exists){
 		sleep(time_input);
		rotation(directory, l, program, number);
	} else {
    fprintf(stderr, "Error: el archivo %s no existe\n", l);
  }

	closedir(dir);
}


//Se reciben, path completo, archivo a rotar, numero de rotaciones y tiempo

int main(int argc, char *argv[]) {
	int number, time_input;


  //verificar numero de parametros
	if (argc != 5){
		fprintf(stderr, "Forma de uso: %s directorio_log archivo_log numero tiempo\n", argv[0]);
		return -1;
	}

  //verificar que sean validos los 2 enteros a recibir, que son el numero de logs y el tiempo.
	number = atoi(argv[3]);
	time_input = atoi(argv[4]);
	if (number <= 0 || time_input <= 0){
		fprintf(stderr, "Error: el programa recibe un numero entero positivo mayor a 0\n");
		return -1;
	}

  //pasar a validacion del directorio
	open_directory(argv[1], argv[0], argv[2], time_input, number);

	return 0;
}
