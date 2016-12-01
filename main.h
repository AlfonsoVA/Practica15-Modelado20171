#ifndef MAIN_H // Guarda para evitar include circulares
#define MAIN_H
/* ------ Se hacen todos los includes necesarios ------ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* ------ Definición de tus estructuras ------ */
//definimos la estructura
struct elemento{
	struct elemento *siguiente;
	void *valor;
	int veces_repetido;
};	
	
//alias para los datos (struct elemento) y (Elemento**)
typedef struct elemento Elemento; 
typedef Elemento** Lista; 

/* ------ Definición de tus funciones ------ */
Lista crea_lista();
int inserta_elemento(Lista lista, void *valor);
int repetido(Lista lista, void *valor);
size_t longitud(Lista lista);
char* el_mas_repetido(Lista lista);
int num_veces_repetido(Lista lista);

/*Imprime las instrucciones de uso del programa*/
void imprime_instrucciones();

#endif //MAIN_H
