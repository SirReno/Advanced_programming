#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct point {
	float x, y;
} Point;


int main(void)
{
  int size;
  float x,y;


  FILE *in_file;
	in_file=fopen("input.txt", "r");

	if(in_file == NULL){
		printf("Cant Read");
	}else{
		fscanf(in_file, "%d",&size);
    printf("%d \n",size);

    for(int i=0; i<size;i++){
        fscanf(in_file, "%f %f",&x, &y);

        Point p={x,y};
        printf("%f %f\n", x ,y);
      }

	}

}
