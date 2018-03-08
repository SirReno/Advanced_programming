/*
	Rodolfo Rincon Muñoz
	A01206310
	Advanced Programing
	Pointers
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define debug 0
/* compile: gcc exercise1.c -lm */
/* execute: ./a.out < input.txt */

typedef struct point {
	float x, y;
} Point;

/* Variables globales. En esta variables se almacenaran
   la cantidad de elementos leidos (size) y los valores
   leídos (points) */
Point *points;
int size;

/* Regresa la distancia entre dos puntos dados (p1, p2) */
float distance(const Point *p1, const Point *p2) {
	return sqrt( ((p2->x - p1->x) * (p2->x - p1->x)) +
		         ((p2->y - p1->y) * (p2->y - p1->y)) );
}

/* A IMPLEMENTAR
   Carga los datos de entrada entandar (consola). Primero
   recibe la cantidad de elementos a leer (size), seguido por
   por 'size' pares de flotantes, los puntos a leer */
void load_data() {
  float x,y;

  FILE *in_file;
	in_file=fopen("input.txt", "r");

	if(in_file == NULL){
		printf("Cant Read");
	}else{
		fscanf(in_file, "%d",&size);
		if (debug){
			printf("%d", size);
		}
		points = (Point*) malloc(size * sizeof(Point));

    for(int i=0; i<size;i++){

        fscanf(in_file, "%f %f",&x, &y);
				Point p={x,y};
				points[i]=p;
				if(debug){
					printf("%f %f\n", x ,y);
				}

      }
	}

}


/* A IMPLEMENTAR
   Regresa el apuntador al punto leído (points) más
   cercano a p */
Point* get_near_from(const Point* p) {
	Point *near = NULL;
	Point *p_aux;
	//distance(const Point *p1, const Point *p2) ;
	float aux, min=100;
	for(int i=0; i< size; i++){
		p_aux=&points[i];
		aux=distance(p,p_aux);
		if(aux<min){
			min=aux;
			near=&points[i];
		}
	}
	return near;
}


/* A IMPLEMENTAR
   Regresa un arreglo de puntos (array) conteniendo los
   últimos num elementos del arreglo points. */
Point* get_last_elements(int num) {
	if(!debug){
		printf("\ncurrently in Get Last elements\n");
	}
	int last, first;
    Point* array = NULL;
		//se necesita darle el espacio para que pueda tener las direcciones de num localidades
    array = (Point*) malloc((sizeof (Point) * num));

    for(last = size - num, first = 0; last < size; last++, first++){
        array[first] = points[last];
    }

    return array;
}


/* A IMPLEMENTAR
   Recibe un arreglo de puntos cualesquiera (array)y la cantidad
   de elementos a desplegar (num). Despliega los elementos en el
   formanto '(x, y)' */
void display_points(Point *array, int num) {
	int i;

	for(i=0; i<num; i++){
		printf("(%f , %f)\n", array[i].x, array[i].y);
	}
}

int main(int argc, char* argv[]) {
	Point p = {0.0, 0.0};
	Point *lasts, *near;

	load_data();
	printf("first 20: \n");
	display_points(points, 20);

	near = get_near_from(&p);
	printf("\n near = (%4.2f, %4.2f)\n", near->x, near->y);

	lasts = get_last_elements(20);
	printf("\n last 10: ");
	display_points(lasts, 10);

	free(points);
	free(lasts);
	return 0;
}
