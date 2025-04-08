#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stddef.h>


//--------------------------------------------------------------------
//--------------------------------------------------------------------
//FUNCOINES PARA LISTAS
//--------------------------------------------------------------------
//--------------------------------------------------------------------

/*
 * 	Struct de los nodos de la lista enlazada simple
 * 
 * */
struct nodo{
    
    char* texto;
    struct nodo* siguiente;
    
};


/*
 * Struct de la lista enlazada simple
 * 
 * */
struct lista{
    
    struct nodo* inicio;
};


/*
 * Funcion que crea listas
 * E: N/A
 * S: Retorna un struct lista con espacio en memoria
 * 
 * */
struct lista* nueva_lista(){
    struct lista *L1 = calloc(1, sizeof(struct lista));
    return L1;
};


/* Funcion que crea nodos       
 *E: Un arreglo de caracteres
 *S: Retorna un puntero con la direccion de memoria del nodo creado
 *R: La entrda tiene que ser un arreglo de caracteres
 */
struct nodo* crear_nodo(char* texto){
    
     
    struct nodo* nuevo_nodo = NULL;
    nuevo_nodo = calloc(1, sizeof(struct nodo));
    nuevo_nodo -> texto = texto;
    nuevo_nodo -> siguiente = NULL;
    return nuevo_nodo;
};


/* Funcion que inserta el numero ingresado al final de la lista
 * E: un puntero hacia un struct lista y arreglo de caracteres
 * S: no retorna nada solo inserta el nodo con el texto ingresado
 * R: la lista de la entrada tiene que ser diferente de NULL 
 */
int insertar_final(struct lista* listaa, char* texto){
    
    
    if(listaa == NULL){
        return -1;
    }
    
    if(listaa -> inicio == NULL){
        
        struct nodo* nuevo_nodo = crear_nodo(texto);
        listaa -> inicio = nuevo_nodo;
        return 0;
        
    } else {
        
        struct nodo* actual = listaa -> inicio;
        while(actual != NULL){
            if(actual -> siguiente == NULL){
                struct nodo* nuevo_nodo = crear_nodo(texto);
                actual -> siguiente = nuevo_nodo;
                return 0;
                
            } actual = actual -> siguiente;
        }
        
        
    }
}
/* Funion que imprime todos los elementos de la lista    
 * E: Una lista
 * S: todos los elementod de la lista
 * R: la lista de la entrada no puede ser NULL y no puede esta vacia
 */
int imprimir_lista(struct lista* listaa){
    
    
    if(listaa == NULL){
        return -1;
    }
    
    if(listaa -> inicio == NULL){
        
        return -1;
    }
    
    struct nodo* actual = listaa -> inicio;
    while(actual != NULL){
        
        printf("%s",actual -> texto);
        printf("\n");
        actual = actual -> siguiente;
    }
}



//--------------------------------------------------------------------
//--------------------------------------------------------------------
//FUNCOINES PARA EL ARBOL
//--------------------------------------------------------------------
//--------------------------------------------------------------------


/*
 * Struct de los nodos del arbol
 * */
struct nodo_arbol{
    char* valor;
    struct lista* Lista;
    struct nodo_arbol* izq;
    struct nodo_arbol* der;
};

/*
 * Struct del arbol
 * */
struct arbol{
    struct nodo_arbol* raiz;
};

/*
 * Crea un espacio en memoria de tipo sturct arbol
 * Retorna el puntero a ese espacio
 * */
struct arbol* nuevo_arbol(){

    struct arbol* arbol1 = calloc(1, sizeof(struct arbol));
    return arbol1;
};

/*
 * Crear una espacio de tipo struct nodo arbol en el heap y le 
 * asigna la dirreccion en memoria a nuevo_nodo, ademas le ingresa 
 * el valor, y la lista es sus respectivas secciones
 * */
struct nodo_arbol* crear_nodo_arbol(char* valor, struct lista* lis){     
    struct nodo_arbol* nuevo_nodo = NULL;
    nuevo_nodo = calloc(1, sizeof(struct nodo_arbol));
    nuevo_nodo -> valor = valor;
    nuevo_nodo -> Lista = lis;
    nuevo_nodo -> izq = NULL;
    nuevo_nodo -> der = NULL;
    return nuevo_nodo;
}

/*
 * Recibe una raiz de un arbol, un valor y una lista
 * Crea un nodo y por medio de recursividad busca donde se 
 * debe insertar(comparando valores)
 * Inserta el nuevo_nodo en el arbol y lo retorna
 * */
struct nodo_arbol* insertar_nodo(struct nodo_arbol* raiz, char* valor, struct lista* lista_archivos){

	if(raiz == NULL){
	
		struct nodo_arbol* nn = crear_nodo_arbol(valor, lista_archivos);
		return nn;
	}
	
	else if(strcmp(raiz -> valor, valor) > 0){
		
		raiz -> izq = insertar_nodo(raiz -> izq, valor, lista_archivos);
	}
	
	else if(strcmp(raiz -> valor, valor) < 0){
		
		raiz -> der = insertar_nodo(raiz -> der, valor, lista_archivos);
	}
	
	return raiz;
}


/*
 * Recibe una struct arbol, un valor y una lista
 * Si el arbol esta vacio, crea un nodo y lo inserta en la raiz
 * Si el arbol no esta vacio llama a insertar_nodo
 * */
struct nodo_arbol* insertar_nodo_aux(struct arbol* arbol1,char* valor,struct lista* lista_archivos){
    if (arbol1->raiz==NULL){
        struct nodo_arbol* nn = crear_nodo_arbol(valor, lista_archivos);
        arbol1->raiz = nn;
        return arbol1 -> raiz;
    }
    
    else{
        return insertar_nodo(arbol1->raiz, valor, lista_archivos);
    }
}

/*
 * Recibe una raiz de un arbol y un valor
 * Busca el nodo que tenga el mismo valor que se recibio de parametro
 * Si lo encuetra devuelve ese nodo, si no devuelve NULL
 * */
struct nodo_arbol* buscar_nodo(struct nodo_arbol* raiz,char* valor){
    
    if (raiz==NULL){
        return NULL;
    }
    
    else if (strcmp(raiz->valor, valor)>0){
        return buscar_nodo(raiz->izq, valor);
    }
    
    else if (strcmp(raiz->valor, valor)<0){
        return buscar_nodo(raiz->der, valor);
    }
    
    else if (strcmp(raiz->valor, valor)==0){
        return raiz;
    }
}

/*
 * Recibe una raiz de un arbol
 * Por medio de recursividad busca el valor más pequeño del arbol
 * Si la lista no esta vacia retorna el valor minimo.
 * */
struct nodo_arbol* minimo(struct nodo_arbol* raiz){
    
    if (raiz==NULL){
        return NULL;
    }
    
    else if (raiz->izq == NULL){
        return raiz;
    }
    else{
        return minimo(raiz->izq);
    }
}

/*
 * Recibe una raiz de un arbol y un valor
 * Busca un nodo por medio de recursividad y lo elimina
 * Si no encuentra al nodo returna null
 * */
struct nodo_arbol* eliminar_nodo(struct nodo_arbol* raiz,char* valor){
	
    if (raiz==NULL){
        return NULL;
    }
    else if (strcmp(raiz->valor, valor)>0){
        raiz->izq = eliminar_nodo(raiz->izq, valor);
    }
    else if (strcmp(raiz->valor, valor)<0){
        raiz->der = eliminar_nodo(raiz->der, valor);
    }
    else{
        struct nodo_arbol* temporal = minimo (raiz->der);
        struct nodo_arbol* subarbol=NULL;
        
        if (raiz->izq != NULL && raiz->der != NULL){
            raiz->valor = temporal->valor ;
            raiz->der = eliminar_nodo(raiz->der, temporal->valor);
            return raiz;
        }
        else{
            temporal = raiz;
            if (raiz->izq == NULL){
                subarbol = raiz->der;
            }
            if (raiz->der == NULL){
                subarbol = raiz->izq;
            }
            free (temporal);
            return subarbol;
        }
    }
    return raiz;
}

/*
 * Recibe un arbol y un valor
 * Verifica si queremos eliminar la raiz y si el arbol}
 * tiene subarbol derecho e izquiero
 * Si no tiene alguno de los dos cambia la raiz por el subarbol que si tenga
 * Si no cae en ninguno de estos casos, llama a la funcion eliminar_nodo
 * */
struct nodo_arbol* eliminar_aux(struct arbol* Arbol, char* valor){
    if (Arbol->raiz->der == NULL){
        if (strcmp(Arbol->raiz->valor, valor)==0){
        struct nodo_arbol* temporal1 = Arbol->raiz;
        struct nodo_arbol* temporal2 = Arbol->raiz->izq;
        free(temporal1);
        Arbol->raiz = temporal2;
        }
    }
    
    else if (Arbol->raiz->izq == NULL){
        if (strcmp(Arbol->raiz->valor, valor)==0){
        struct nodo_arbol* temporal1 = Arbol->raiz;
        struct nodo_arbol* temporal2 = Arbol->raiz->der;
        free(temporal1);
        Arbol->raiz = temporal2;
        }
    }
    else{
        return eliminar_nodo(Arbol->raiz, valor);
    }
}

/*
 * Recibe una raiz de un arbol
 * Se encarga de hacer una rotacion a la derecha
 * retorna la raiz con la rotacion hecha
 * */
struct nodo_arbol* rotacionDerecha(struct nodo_arbol* nodo){
    struct nodo_arbol* nodoNuevo = nodo->izq;
    nodo->izq = nodoNuevo->der;
    nodoNuevo->der = nodo;
    return nodoNuevo;
}

/*
 * Recibe una raiz de un arbol
 * Se encarga de hacer una rotacion a la izquierda
 * retorna la raiz con la rotacion hecha
 * */
struct nodo_arbol* rotacionIzquierda(struct nodo_arbol* nodo){
    struct nodo_arbol* nodoNuevo = nodo->der;
    nodo->der = nodoNuevo->izq;
    nodoNuevo->izq = nodo;
    return nodoNuevo;
}

/*
 * Recibe una raiz y un nodo
 * Por medio de recursividad busca el nodo padre del nodo que recibe
 * de parametro
 * Si lo encuentra devuelve el nodo padre, si no devuelve NULL
 * 
 * */
struct nodo_arbol* padre(struct nodo_arbol* raiz, struct nodo_arbol* nodo){
    if (raiz==NULL || raiz == nodo){
        return NULL;
    }
    
    if(raiz->izq == nodo || raiz->der == nodo){
        return raiz;
    }
    
    if (strcmp(raiz->valor, nodo->valor)>0){
        return padre(raiz->izq, nodo);
    }
    
    if (strcmp(raiz->valor, nodo->valor)<0){
        return padre(raiz->der, nodo);
    }
}

/*
 * Recibe una raiz de un arbol y un nodo
 * Por medio de recursividad busca donde se encuetra el nodo
 * Dependiendo de en que casos entre se va a ir rotando el nodo hacia arriba
 * Retorna el nodo de parametro como la nueva raiz del arbol
 * */
struct nodo_arbol* splay(struct nodo_arbol* raiz, struct nodo_arbol* nodo){
    
    //si la raiz es nula o es la que busco retorno la raiz 
    if (raiz==NULL || raiz==nodo){
        return raiz;
    }
    
    //si el nodo esta en el izquierdo (zag)
    else if(raiz->izq == nodo){
        raiz = rotacionDerecha(raiz);
        return raiz;
    }

    //si el nodo esta en el derecho (zig)
    else if(raiz->der == nodo){
        raiz = rotacionIzquierda(raiz);
        return raiz;
    }
    else if(strcmp(raiz->valor, nodo->valor)>0){
        if (strcmp(raiz->izq->valor, nodo->valor)>0){
            if(raiz->izq->izq == nodo){
                raiz = rotacionDerecha(raiz);
                raiz = rotacionDerecha(raiz);
                return raiz;
            }
            else{
                raiz->izq = splay(raiz->izq, nodo);
                raiz = rotacionDerecha(raiz);
            }
        }
    
        else if (strcmp(raiz->izq->valor, nodo->valor)<0){
            if(raiz->izq->der == nodo){
                raiz->izq = rotacionIzquierda(raiz->izq);
                raiz = rotacionDerecha(raiz);
            }
            else{
                raiz->izq = splay(raiz->izq, nodo);
                raiz = rotacionDerecha(raiz);
            }
        }
    }

    else{
        if (strcmp(raiz->der->valor, nodo->valor)<0){
            if(raiz->der->der == nodo){
                raiz = rotacionIzquierda(raiz);
                raiz = rotacionIzquierda(raiz);
                return raiz;
            }
            else{
                raiz->der = splay(raiz->der, nodo);
                raiz = rotacionIzquierda(raiz);
            }
        }

        else if (strcmp(raiz->der->valor, nodo->valor)>0){
            if(raiz->der->izq == nodo){
                raiz->der = rotacionDerecha(raiz->der);
                raiz = rotacionIzquierda(raiz);
                return raiz;
            }
            else{
                raiz->der = splay(raiz->der, nodo);
                raiz = rotacionIzquierda(raiz);
            }
        }
    }
}

/*
 * Recibe una raiz de un arbol
 * Imprime el valor de cada nodo del arbol en preorden
 * */
void imprimir_preorden(struct nodo_arbol* raiz){
    if (raiz==NULL){
        return;
    }
    
    printf("%s\n",raiz->valor);
    imprimir_preorden(raiz->izq);
    imprimir_preorden(raiz->der);
}

/*
 * Recibe una raiz de un arbol
 * Imprime el valor de cada nodo y el contenido de la lista
 * */
void imprimir_preorden_lista(struct nodo_arbol* raiz){
    if (raiz==NULL){
        return;
    }
    
    printf("%s\n",raiz->valor);
    imprimir_lista(raiz->Lista);
    imprimir_preorden_lista(raiz->izq);
    imprimir_preorden_lista(raiz->der);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
//FUNCIoNES PARA LA TABLA
//--------------------------------------------------------------------
//--------------------------------------------------------------------

/*Funcion que dice si un numero es primo o no
 * E: Un numero entero positivo(preferiblemente primo)
 * S: Un 1 si el numero es primo y un 2 si no
 * R: La entrada tiene que ser un numero primo preferiblemente
 * */ 
int esPrimo(int numero) {

	
    if (numero == 0 || numero == 1) 
        return 0;
  
    if (numero == 4) 
        return 0;
  
    for (int x = 2; x < numero / 2; x++) {
    
        if (numero % x == 0) 
            return 0;
    }
  return 1;
}


/*Funcion que retorna el siguiente primo al numero de la entrada
  * E: Un numero entero
  * S: Un numero entero que es primo 
  * R: La entrada preferiblemente tiene que ser un numero primo
  * */
int siguientePrimo(int numero){
    
    int actual = numero;
    while(1){
    
        actual++;
        if(esPrimo(actual)) 
        return actual;
    }
}



//--------------------------------------------------------------------
//--------------------------------------------------------------------
//FUNCIONES PARA LA TABLA DE HASH
//--------------------------------------------------------------------
//--------------------------------------------------------------------

int largo = 11;
int largoAux=19;


/* Funcion hash 
 * E: Un puntero a un char
 * S: Un numero entero resultado del algoritmo de la funcion
 * R: N/A
 * */
int funcionhash(char* llave){
	
    int contador = 0;
    int i =0;
    int j =1;
    
    while (llave[i] != '\0'){
        contador+= llave[i]*j;
        i++;
        j++;
    }

    return contador;
}


/*Struct de un nodo de la tabla hash
 * */
struct nodo_tabla{
	
    char* llave;
    char* contenido;
};


/*Crear una espacio de tipo struct nodo_tabla** en el heap y le 
 * asigna la dirreccion en memoria a nueva_lista
 * */
struct nodo_tabla** nueva_tabla(int largo_tabla){
    
    struct nodo_tabla** tabla_hash = calloc(largo_tabla, sizeof(struct nodo_tabla*));
    return tabla_hash;
};


/* Funcion que crea nodos de tabla de hash asignandoles espacio en memoria
 * E: Dos punteros a un char  
 * R: N/A
 * */
struct nodo_tabla* crear_nodo_tabla(char* llave, char* contenido){
    
    struct nodo_tabla* nuevo_nodo = NULL;
    
    
    nuevo_nodo = calloc(1, sizeof(struct nodo_tabla));
    nuevo_nodo -> llave = llave;
    nuevo_nodo -> contenido = contenido;
    
    
    return nuevo_nodo;
}

/* Funcion que obtiene el largo de un archivo 
 * E: La direccion/ruta del archivo a ser medido
 * S: Un numero entero que dice la cantidad de caracteres
 * R: N/A
 * 
 * */
int largo_archivo(char* direccion){

    int cont = 0;
    
    FILE* archivo = fopen(direccion, "r");

    if(archivo == NULL){
        return -1;
    }

    while (1){
        
        fgetc(archivo);
        cont++;
        
        if (feof(archivo) != 0){
            break;
        }
    }

    fclose(archivo);    
    return cont;
}

/* Funcion que convierte todo el contenido de un archivo de texto en un solo char
 * E: Un arreglo de caracteres que es el nombre del archivo
 * S: Un arreglo de caracteres
 * R: N/A
 * 
 * */
char* leer_archivo(char* arch){
	
	char  direccion[20] = "test/";
    
    char  documento[100]; // Ruta completa del archivo
    
    strcpy(documento, direccion);
    
    strcat(documento,arch);
    
    
    char reglon[200];
    int lenTexto = largo_archivo(documento);
    char texto_total[1000000] = {0};
    
    FILE* archivo = fopen(documento, "r");
    
   
	while (1){
		
		fgets(reglon, 200, archivo);
		strcat(texto_total, reglon);
		
		
		if(feof(archivo) != 0){
		   break;
		}
		
	}
	
	fclose(archivo);
	
	char* texto_total_heap = calloc(lenTexto, sizeof(char));
	strcpy(texto_total_heap, texto_total);
	return texto_total_heap;
	
}

/* Funcion que redimensiona una tabla de hash
 * E: Un struct de tabla de hash
 * S: Un struct de tabla de hash ya redimensionado
 * R: N/A
 * 
 * */
struct nodo_tabla** redimencionamiento(struct nodo_tabla** tabla_hash){
    struct nodo_tabla** siguiente_hash = nueva_tabla(largoAux);
    
    for (int i =0;i<largo;i++){
        if (tabla_hash[i]!=NULL){
            int valor_hash = funcionhash(tabla_hash[i]->llave);
            int posicion = valor_hash%largoAux;
            if (siguiente_hash[posicion]!=NULL){
                while (siguiente_hash[posicion]!=NULL){
                    if (posicion==largoAux-1){
                        posicion=-1;
                    }
                    posicion++;
                }
            siguiente_hash[posicion]=tabla_hash[i];
            tabla_hash[i]=0;
            }
            else{
                siguiente_hash[posicion]=tabla_hash[i];
                tabla_hash[i]=0;
            }
        }
    }
    free(tabla_hash);
    tabla_hash=siguiente_hash;
    siguiente_hash=0;
    largo=largoAux;
    largoAux=siguientePrimo(largoAux);
    return tabla_hash;
}


/* Funcion que inserta todos los archivos de un directorio y el contenido de estos dentro de una tabla de hash
 * E: Un struct de tabla de hash
 * S: Una tabla de hash con todos los archivos insertados
 * R: N/A
 * */
struct nodo_tabla** insertar_archivo(struct nodo_tabla** tabla_hash) { 
	
	DIR *d; 
	
	struct dirent *dir; 
	
	d = opendir("test");    
 
	if (d) { 
		while ((dir = readdir(d)) != NULL) { 
			
			if(strcmp(dir->d_name, "..")!=0 && strcmp(dir->d_name, ".")!=0){
				
			int largostring = strlen(dir -> d_name);
			char* llave = calloc(largostring, sizeof(char));
			strcpy(llave, dir -> d_name);
			
			char* contenido = leer_archivo(dir -> d_name);
			struct nodo_tabla* nn = crear_nodo_tabla(llave, contenido);
			
			int valor_hash = funcionhash(dir->d_name);
			int posicion = valor_hash%largo;
			
			if (tabla_hash[posicion]==NULL){
				
				tabla_hash[posicion]=nn;
				
				
				//Aquí comienza a redimensionar la tabla
                int espacios_ocupados = 0;

                for (int i =0;i<largo;i++){
                    if (tabla_hash[i]!=NULL){
                        espacios_ocupados++;
                    }
                }
			
                if (75*largo/100 == espacios_ocupados){
                    tabla_hash=redimencionamiento(tabla_hash);
                }
                espacios_ocupados = 0;
			}
			
			else{
				while (tabla_hash[posicion]!=NULL){
					if (posicion==largo-1){
						posicion=-1;
					}
					posicion++;
				}
				tabla_hash[posicion]=nn;
				
                //printf("-----------------------------------------------\n");
                int espacios_ocupados = 0;

                for (int i =0;i<largo;i++){
                    if (tabla_hash[i]!=NULL){
                        espacios_ocupados++;
                    }
                }
                if (75*largo/100 == espacios_ocupados){
                    tabla_hash=redimencionamiento(tabla_hash);
                }
                espacios_ocupados = 0;
            }
        } 
	}
    closedir(d); 
    }
    return tabla_hash;
}





/* Funcion que imprime una tabla de hash
 * E: Un struct de tabla de hash
 * S: N/A, imprime la tabla de hash
 * R: N/A
 * 
 * */

void imprimir_tabla(struct nodo_tabla** tabla_hash){
	
	printf("INICIO\n");
	
	for(int i=0; i < largo; i++){
		if(tabla_hash[i] == NULL){
			printf("\t%i\t---\n",i);
		} else{
			printf("\t%i\t%s\n ",i, tabla_hash[i]->llave);
			
		}
	}
	printf("FINAL\n");
}

 

/* Funcion que revisa linea por linea de un archivo .txt la existencia de la cadena de la entrada
 * 
 * E: Dos punteros a char
 * S: Retorna un 1 si se encontro la palabra o frase dentro de texto y un 0 si no.
 * 
 * */
int encontrar_subcadenas (char *linea, char *palabra_frase){
  
  for (; *linea; ++linea){
    
      char *subcadena = palabra_frase;
      char *cadena = linea;
      
      while (*subcadena == *cadena && *subcadena){
      
		subcadena++;
		cadena++;
	  }


      if (*subcadena == '\0')
		return 1;
   }

  return 0;
}



/* Funcion que busca una palabra o frase dentro de los textos en una tabla de hash
 * E: Un struct de tabla de hash, un puntero a char que es la palabra a encontrar y un struct de arbol
 * S: Imprime todos los archivos en los que se encontro esa palabra
 * R: N/A
 * 
 * */
int buscar_palabra_frase(struct nodo_tabla** tabla_hash, char* palabra_buscada, struct arbol* arbol1 ){
    
    struct nodo_arbol* miNodo = buscar_nodo(arbol1->raiz,palabra_buscada);
    if (miNodo!=NULL){
        imprimir_lista(miNodo->Lista);
        arbol1 -> raiz = splay(arbol1-> raiz,miNodo);
        return 0;
    }
    else{
        struct lista * l1 = NULL;
        l1 = nueva_lista();
	
        for(int i = 0; i<largo; i++){
            if(tabla_hash[i] != NULL){
                if(encontrar_subcadenas(tabla_hash[i] -> contenido,palabra_buscada) == 1){
                    insertar_final(l1,tabla_hash[i] -> llave);
					
                }
			
            }
        }
	
        if(l1 -> inicio == NULL){
		
            l1 = NULL;
            free(l1);
            printf("---------------------------------\n");
            printf("[Err0r] la palabra no ha sido encontrada en ningun archivo\n");
            return 0;
        } 
        else{
            insertar_nodo_aux(arbol1, palabra_buscada, l1);
            struct nodo_arbol* miNodo1 = buscar_nodo(arbol1->raiz,palabra_buscada);
            arbol1 -> raiz = splay(arbol1-> raiz,miNodo1);
            printf("---------------------------------\n");
            printf("La palabra ha sido encontrada en los siguientes arhcivos:\n");
            printf("\n");
            imprimir_lista(l1);
            return 0;
        }
    }
}



/*Funcion que busca un archivo dentro de una tabla de hash
 * E: Un struct de tabla de hash y un puntero a un char que es el archivo a buscar
 * S: Imprime el contenidharo del archivo buscado.
 * R: N/A
 * 
 * */
int buscar_documento(struct nodo_tabla** tabla_hash,  char* doc){
	
	

	int valor_hash = funcionhash(doc);
	int posicion = valor_hash%largo; 
	

	if(strncmp(tabla_hash[posicion]->llave, doc, 256) == 0){
		printf("[Ok] Archivo encontrado\n");
		printf("El contenido del archivo es: \n");
		printf("%s\n", tabla_hash[posicion] -> contenido);
		return 1;
	}
	
	else{

		while (tabla_hash[posicion]!=NULL){
			if(strncmp(tabla_hash[posicion]->llave, doc, 256) == 0){
				printf("[Ok] Archivo encontrado\n");
				printf("El contenido del archivo es: \n");
				printf("%s\n", tabla_hash[posicion] -> contenido);
				return 1;
			}
            if (posicion==largo-1){
                posicion=-1;
            }
            posicion++;
            
        }
        
	}
	printf("[Err0r] Archivo no encontrado.\n");
	
	return 0;
}


//--------------------------------------------------------------------
//--------------------------------------------------------------------
//FUNCIONES PARA EL CACHE
//--------------------------------------------------------------------
//--------------------------------------------------------------------


/* Funcion que guarda el arbol de cache en disco
 * E: Un struct nodo_arbol
 * S: N/A
 * R: N/A
 * */
int guardar_cache(struct nodo_arbol* raiz){
	
	if(raiz == NULL){	
		return -1;
	}
	
	FILE* archivo;
	
	archivo = fopen("cache.txt", "a+");
	
	fprintf(archivo,"%s",raiz->valor);
	fprintf(archivo,"] ");
	struct nodo* actual = raiz -> Lista -> inicio;
    while(actual != NULL){
        if(actual -> siguiente == NULL){
			fprintf(archivo,"%s\n",actual -> texto);
			actual = actual -> siguiente;
			continue;
		}else{
			fprintf(archivo,"%s ",actual -> texto);
        
			actual = actual -> siguiente;
		}
    }
    
    fclose(archivo);
    guardar_cache(raiz->izq);
	guardar_cache(raiz->der);
	
}


// Funcion que reinicia el cache
int reiniciar_cache(){

	FILE* archivo;
	
	archivo = fopen("cache.txt","w");
	
	fprintf(archivo," ");
	fclose(archivo);
}



/* Funcion que carga el cache que esta en disco al programa. 
 * E: Un struct de un arbol y un numero entero que dice que linea del disco tiene que leer
 * S: N/A
 * R: N/A
 * */
int cargar_cache(struct arbol* arbol1, int vuelta){
	

	
	FILE* archivo;
	archivo = fopen("cache.txt","r");
	
	char* reglon = calloc(20000,sizeof(char));
	fseek(archivo, 1, SEEK_SET);
	
	
	int j = 1;
	if(j == vuelta){
		fgets(reglon, 20000, archivo);
	}else{	
		while(j <= vuelta){
		
			fgets(reglon, 20000, archivo);
			j++;
		}	
	}	
	reglon[strlen(reglon)-1] = '\0';
	char* palabra = calloc(20,sizeof(char));	
	char* txt = calloc(100,sizeof(char));	
	struct lista* l1 = NULL;
	l1 = nueva_lista();
			
	char* token;
	token = strtok(reglon, "]");
	int i = 0;
	
	while(token != NULL){
		if(i == 0){
		palabra = token;
		token = strtok(NULL, " ");
		i++;
				
		} else{
					
			txt = token;
			insertar_final(l1, txt);
			token = strtok(NULL, " ");
		}
		
		
	}
			
	insertar_nodo_aux(arbol1,palabra,l1);
	fclose(archivo);
	return 0;
	
}

/* Funcion que comprueba si un archivo esta vacio o no
 * E: N/A
 * S: Un 0 si el archvio esta vacio y si no un 1
 * */
int txt_vacio(){
	
	FILE* archivo;
	archivo = fopen("cache.txt", "r");
	
	fseek(archivo, 0, SEEK_END);
	
	if(ftell(archivo) == 0){
		return 0;
	} else{
		return 1;
	}

}


// Funcion que muestra el menu
int menu(){
	
	
	int i = 1;
	char* reglon = calloc(20000,sizeof(char));

	FILE* archivo;
	archivo = fopen("cache.txt","r");
	fseek(archivo, 2, SEEK_SET);
	
    struct nodo_tabla** tabla_hash = NULL;
    tabla_hash = nueva_tabla(largo);
    tabla_hash = insertar_archivo(tabla_hash);
    
    struct arbol * arbol1 = NULL;
    arbol1 = nuevo_arbol();
    
    if(txt_vacio() == 1){
		
		while(fgets(reglon, 20000, archivo) != 0){
		cargar_cache(arbol1,i);
		i++;
		}
	}
		

    
    int opcion;
    char llave[100];
    

    
    while(1){
        printf("\n");
        printf("-----------------------------------------------\n");
        printf("Que desea hacer?\n\n");
        printf("1. Buscar palabra o frase\n"); 
        printf("2. Buscar documento\n"); 
        printf("3. Mostrar todos los documentos\n"); 
        printf("4. Mostrar cache\n"); 
        printf("5. Mostrar lista del cache\n"); 
        printf("6. Salir\n"); 
        printf("Ingrese una opcion => ");
        scanf("%d",&opcion);
        while(getchar()!='\n');
        printf("\n");
        
        
        
        
        if (opcion==6){
			reiniciar_cache();
			guardar_cache(arbol1 -> raiz);
            break;
        }
        
        if (opcion==1){
			
			printf("\n");
            printf("Palabra o frase que desea buscar: ");
            scanf("%[^\n]",llave);
            while(getchar()!='\n');
             
            
            char* llave_heap = calloc(100,sizeof(char));
            strcpy(llave_heap,llave);
            
            buscar_palabra_frase(tabla_hash, llave_heap, arbol1);
            
			
        }   


        if (opcion==2){
			
			printf("\n");
            printf("Nombre del documento que desea buscar: ");
            scanf("%[^\n]",llave);
            while(getchar()!='\n');
             
            
            char* llave_heap = calloc(100,sizeof(char));
            strcpy(llave_heap,llave);
            buscar_documento(tabla_hash, llave_heap);
            
            
        
        }
        
        if (opcion==3){
           imprimir_tabla(tabla_hash);
        }
        
        if(opcion == 4){
			imprimir_preorden(arbol1 ->raiz);
		}
        
        if(opcion == 5){
			imprimir_preorden_lista(arbol1 ->raiz);
		}
        
	}
        
    
}


int main() {
    
    menu();
    
    return 0;
}
