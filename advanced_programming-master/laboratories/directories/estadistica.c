#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#define DEBUG 0

float regular=0;
float directories=0;
float fifo=0;
float links=0;
float total=0;

void get_info_from_dir(char* path, char* file, char* program) {
	struct stat buf;
	char f_name[NAME_MAX + 1];

	sprintf(f_name, "%s/%s", path, file);
  //verificar el archivo
	if (lstat(f_name, &buf) == -1) {
		printf("f_name: %s\n", f_name);
		perror(program);
		exit(-1);
	}
  if(DEBUG){
      printf("Counting\n");
  }

	if (S_ISREG(buf.st_mode)){
    if(DEBUG){
      printf("REGULAR\n" );
    }
    regular++;
    total++;
  }else if (S_ISDIR(buf.st_mode)){
    if(DEBUG){
      printf("DIR\n" );
    }
    directories++;
    total++;
  }else if (S_ISFIFO(buf.st_mode)){
    if(DEBUG){
      printf("FIFO\n");
    }
    fifo++;
    total++;
  }else if (S_ISLNK(buf.st_mode)){
    if(DEBUG){
      printf("LINKS\n" );
    }
    links++;
    total++;
  }
}

void print_info(char *dir_name, char* program) {
	char f_name[NAME_MAX + 1];
	DIR* dir;
	struct dirent* dir_entry;
	struct stat buff;
  float sum=0;

	if ( (dir = opendir(dir_name)) == NULL) {
		perror(program);
		exit(-1);
	}

	printf("DIRECTORY = %s\n", dir_name);

	while( (dir_entry = readdir(dir)) != NULL ) {
		if (strcmp(dir_entry->d_name, ".") != 0 && strcmp(dir_entry->d_name, "..") != 0) {
			get_info_from_dir(dir_name, dir_entry->d_name, program);
		}
	}
  if(DEBUG){
    printf("Results\n");
  }

  sum = directories + regular + fifo + links;
	directories = (directories / sum) * 100;
	regular = (regular / sum) * 100;
	fifo = (fifo / sum) * 100;
	links= (links / sum) * 100;

	printf("Type\tPercentage\n");
	printf("DIR\t%f\n", directories);
	printf("REG\t%f\n", regular);
	printf("FIFO\t%f\n", fifo);
	printf("LNK\t%f\n", links);

  if(DEBUG){
    printf("reseted variables\n");
  }
  directories= 0;
  regular = 0;
  fifo = 0;
  links = 0;
  total=0;

  if(DEBUG){
    printf("REWINDING DIR");
  }
  rewinddir(dir);
	while( (dir_entry = readdir(dir)) != NULL ) {
		if (strcmp(dir_entry->d_name, ".") != 0 && strcmp(dir_entry->d_name, "..")) {
      sprintf(f_name, "%s/%s", dir_name, dir_entry->d_name);
			stat(f_name, &buff);
			if (S_ISDIR(buff.st_mode)) {
				print_info(f_name, program);
			}
		}
	}

	closedir(dir);
}


int main(int argc, char* argv[]) {
  char dir_name[NAME_MAX +1];
  char f_name[NAME_MAX+1];
  DIR *dir;

  if(DEBUG){
    printf("1er print, entrando al programa\n");
  }

  if (argc > 2){
    printf("Forma de uso: %s [directorio]\n", argv[0]);
    return -1;
  }
  if(argc==1){
    getcwd(dir_name,NAME_MAX); //get current working directory
  }else{
    strcpy(dir_name, argv[1]); // el directorio indicado, si es que se paso algun directorio
  }

  if((dir=opendir(dir_name))==NULL){
    perror("opendir: el directorio no existe");
    return -1;
  }

  if (DEBUG){
    printf("ya se obtuvo el directorio");
  }

  print_info(dir_name, argv[0]);
  return 0;

}
