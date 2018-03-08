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
#define DEBUG 1


void get_info_from_dir(char* path, char* file, char* program) {
	struct stat buf;
	char f_name[NAME_MAX + 1];
  FILE *in_file;
  int max=0,min=0,num=0,nCount=0;

  if(DEBUG){
    printf("GEtting info\n");
  }

  sprintf(f_name, "%s/%s", path, file);
  //verificar el archivo
  if (lstat(f_name, &buf) == -1) {
		printf("f_name: %s\n", f_name);
		perror(program);
		exit(-1);
	}

  if (S_ISREG(buf.st_mode)){
    if(DEBUG){
      printf("REGULAR\n" );
    }
    in_file=fopen(f_name,"rb");

    while(fscanf(in_file, "%i")!=EOF){
      if(DEBUG){
        printf("IN FOR\n" );
      }
      fscanf( in_file, "%i", &num );
      if( num > max ){
        max = num;
        printf("%i",max);
      }else if( num < min ){
        min = num;
        printf("%i",min);
      }
     }
     fclose(in_file);
    printf("Filename= %s/%s - min = %i - max= %i\n",path, file, min, max);
  }

}


void print_info(char *dir_name, char* program) {
	char f_name[NAME_MAX + 1];
	DIR* dir;
	struct dirent* dir_entry;
	struct stat buff;

  if(DEBUG){
    printf("Print Info\n");
  }
	printf("DIRECTORY = %s\n", dir_name);

  dir=opendir(dir_name);

	while( (dir_entry = readdir(dir)) != NULL ) {
		if (strcmp(dir_entry->d_name, ".") != 0 && strcmp(dir_entry->d_name, "..") != 0) {
      if(DEBUG){
        printf("Before getting info\n");
      }
      get_info_from_dir(dir_name, dir_entry->d_name, program);
		}
	}


  if(DEBUG){
    printf("REWINDING DIRECTORY \n");
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

  struct stat buf;


  if (argc > 2 || argc==1){
    printf("Error\nCorrect usage: %s directory\n", argv[0]);
    exit -1;
  }
  if(DEBUG){
    printf("Before opendir\n");
  }

  strcpy(dir_name, argv[1]);
  if((dir=opendir(dir_name))==NULL){
    perror("Not such a file o directory in opendir");
    return -1;
  }else{
    if(DEBUG){
      printf("Sending to Print info\n");
    }
    strcpy(dir_name, argv[1]); // el directorio indicado, si es que se paso algun directorio
    print_info(dir_name, argv[0]);
  }
  //print_info(dir_name, argv[0]);
  return 0;

}
