
#include "main.h"
// No hagas #include aquí, hazlos en main.h

int main(int argc, char const *argv[]){
    // Verifica si hay al menos de 3 parametros
    // sino entonces se imprimen las instrucciones
    // y se para la ejecución del programa
    if (argc < 3){    	
        imprime_instrucciones();
        return 0;        
    }    
    //Declaramos el arreglo de apuntadoresa FILES, de dimension argc-1 sin contar el argv[0]
    	//luego asignamos a cada apuntador a FILE el nombre de su archivo y la posibilidad de leerlo
    FILE *apunta_entradas[argc-1];	
    int i;
	for(i= 1; i<argc-1; i++){
		apunta_entradas[i-1]= fopen(argv[i], "r");
	}

	//Apuntador a FILE de salida, en este podemos escribir 
	FILE *pointer_salida;
    pointer_salida=fopen(argv[argc-1],"w");

	printf("Nombre del archivo           Palabra más repetida                   Número de repeticiones \n");
	fprintf(pointer_salida, "Nombre del archivo           Palabra más repetida                   Número de repeticiones\n");	

   	for(int i=1; i<argc-1; i++){
   		Lista lista_palabras_total = crea_lista(); 
   		char bofer[300];   	   			 
   		while(fgets(bofer, 300, apunta_entradas[i-1])!= NULL){
   			char *token =strtok(bofer," ,.-\n"); 
   			while(token!=NULL){   				   				  		   	
   				char *palabra= malloc(strlen(token)+1);
   				strcpy(palabra,token);
   				inserta_elemento(lista_palabras_total, palabra);
   				token = strtok(NULL," ,.-\n");  					
   			}   			
   		}   	   		   		 		
   		
		//Imprimimos y agregamos la palabra más repetida con su número correspondiente de repeticiones
   		char *result= el_mas_repetido(lista_palabras_total);  
   		int num_result= num_veces_repetido(lista_palabras_total);
   		printf("%s                             %s                             %d\n", argv[i], result, num_result);
   		fprintf(pointer_salida, "%s                             %s                             %d\n", argv[i], result, num_result);  
   		fclose(apunta_entradas[i-1]); 		   			   		 					   	
   }  
   	printf("Se guardó el resultado en el archivo %s", argv[argc-1]);
    //Cerrando la lectura y escritura de los apuntadores   
    fclose(pointer_salida);
    return 0;
}

/* ------ Aquí va la implementación de tus funciones ------ */
//Si no se cumplen las condiciones de los parametros en el main
void imprime_instrucciones(){
	printf("Error: El formato de entrada es incorrecto\n");
	printf("Uso: programa <archivo> [<archivo> [<archivo> ...]] <archivo>\n");
}

//Crea lista, usando calloc con el sizeof(lista)
Lista crea_lista(){
	Lista la_lista = calloc(1,sizeof(Lista));
	return la_lista;
}

//Se encarga de checar si la palabra ya esta en la lista
int repetido(Lista lista, void *valor){
	Elemento *tmp= *lista;
	int r=0;
	size_t len= longitud(lista);
	for(int i=0; i<len; i++){		
		if(strcmp(tmp->valor, valor)==0){						
			tmp->veces_repetido++;
			r=1;
			return r;
		}else{
			tmp=tmp->siguiente;
		}
	}
	return r;
}

//Agrega el elemento a la lista, si ya esta dicha palabra, solo aumenta el número de repeticiones respecto a la palabra ya agregada
int inserta_elemento(Lista lista, void *valor){			
	int esta_repetido= repetido(lista, valor);	
	if (esta_repetido==1){
		return 0;
	}else{
		Elemento *elem= calloc(1,sizeof(Elemento));			
		elem->siguiente=*lista;
		elem->valor=valor;
		elem->veces_repetido=1;
		*lista= elem;	
		size_t len= longitud(lista);		
		return 1;
	}	
}
//Da la longitud de la lista, la cual solo cuenta con las palabras en total sin importar sus repeticiones
size_t longitud(Lista lista){	
	size_t len= 0;
	Elemento *tmp = *lista;
	while(tmp != NULL){
		len+=1;
		tmp= tmp->siguiente;
	}	
	return len;
}
//Devuelve el la palabra con mayor numero de repeticiones/intentos de inserción a la lista
char* el_mas_repetido(Lista lista){
	Elemento *tmp= *lista;
	int rep= tmp->veces_repetido;
	char *val= tmp->valor;
	size_t len= longitud(lista);
	int i;	
	for(i=0; i<len; i++){
		if(rep<tmp->veces_repetido){
			rep=tmp->veces_repetido;			
			val=tmp->valor;
			tmp= tmp->siguiente;
		}else{
			tmp= tmp->siguiente;
		}			
	}				
	return val;
}
//Devuelve el número de repeticiones/inserciones que se hacen a la palabra con mayor número de estas últimas
int num_veces_repetido(Lista lista){
	Elemento *tmp= *lista;
	int rep= tmp->veces_repetido;
	char *val= tmp->valor;
	size_t len= longitud(lista);
	int i;	
	for(i=0; i<len; i++){
		if(rep<tmp->veces_repetido){
			rep=tmp->veces_repetido;			
			val=tmp->valor;
			tmp= tmp->siguiente;
		}else{
			tmp= tmp->siguiente;
		}			
	}				
	return rep;
}
