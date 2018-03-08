//Rodolfo Rincón Muñoz
//A01206310

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define SIZE 1000

int values[SIZE];
int max_value;
struct stat st = {0};

float normalization(float val) {
    return val/max_value;
}

void create_new_file(char* directory, char* name, char* program, char* new_directory) {
	  FILE *file;
	  FILE *new_file;
	  int time, intersections, size, i;
	  float number;
	  char filename[NAME_MAX + 1], new_filename[NAME_MAX + 1];

    //Pasar el path completo, para cada uno de los archivos
	  sprintf(filename, "%s/%s", directory, name);
	  sprintf(new_filename, "%s/%s", new_directory, name);

	  file = fopen(filename, "r");
	  new_file = fopen(new_filename, "w");

	  if (file == NULL) {
		  perror(program);
		  exit(-1);
	  }

	  if (new_file == NULL) {
		  perror(program);
		  exit(-1);
	  }
    //aqui puedes leer los 2 enteros para mover el apuntador y que continue leyendo los flotantes
	  while ( fscanf(file, "%i,%i", &time, &intersections) != EOF ) {
		  fprintf(new_file, "%i,%i", time, intersections);
		  size = intersections * intersections;
		  for (i = 0; i < size; i++) {
			  fscanf(file, ",%f", &number);
			  fprintf(new_file, ",%f", normalization(number));
        //Aqui lees los numeros flotantes, y de paso guardas el valor maximo que encuentres,
        if(number>max_value){
          max_value=number;
        }
		  }
		  fprintf(new_file, "%d\n", rand() % 100);
	  }

	  fclose(file);
	  fclose(new_file);
}

void read_values(char* directory, char* name, char* program) {
	  FILE *file;
	  int time, intersections, size, i;
	  float number;
	  char filename[NAME_MAX + 1];

	  sprintf(filename, "%s/%s", directory, name);
	  file = fopen(filename, "r");
	  if (file == NULL) {
		  perror(program);
		  exit(-1);
	  }

	  memset(values, 0, SIZE * sizeof(int));

	  while ( fscanf(file, "%i,%i", &time, &intersections) != EOF ) {
	  	size = intersections * intersections;
		  for (i = 0; i < size; i++) {
			  fscanf(file, ",%f", &number);
			  values[ ((int) number) ]++;
		  }
	  }
	  fclose(file);
}

void open_directory(char* directory, char* program, int read, char* new_directory) {
	  DIR *dir;
	  struct dirent *directory_entry;

	  if( (dir = opendir(directory)) == NULL) {
  		perror(program);
  		exit(-1);
	  }

	  while ( (directory_entry = readdir(dir)) != NULL) {
		  if (strcmp(directory_entry->d_name, ".") == 0 ||
			  strcmp(directory_entry->d_name, "..")  == 0) {
			  continue;
		  }

		  if (read) {
			  read_values(directory, directory_entry->d_name, program);
		  }else{
			  if (stat(new_directory, &st) == -1) {
          //el 0700 es el modo en el que crea el archivo, tiene que ver con permisos
          mkdir(new_directory, 0700);
			  }
			  create_new_file(directory, directory_entry->d_name, program, new_directory);
		  }
	  }

	  closedir(dir);
}

int main (int argc, char* argv[]){
    //verificar que sean 3 argumentos, incluyendo el nombre del programa.
  	if (argc != 3) {
  		fprintf(stderr, "usage: %s [directory] [new directory]\n", argv[0]);
  		return -1;
  	}
  	open_directory(argv[1], argv[0], 1, NULL);
  	open_directory(argv[1], argv[0], 0, argv[2]);

  	return 0;
}
