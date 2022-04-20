#include "AniquilamientoPositronicoIonizanteGravitatorio.h"


/* -----------------------------------------
----------------------------------------
--------------------------------------*/

//Funciones auxiliares 
//////////////////////////////////////////////////

//Funcion para crear un nuevo vertice
//Usada en la funcion para agregar un vertice
struct VerticeSt NuevoVertice(u32 n) {

    struct VerticeSt x;
	x.nombreV = n;
	x.colorV = 0;
	x.gradoV = 0;
    x.capacidad_v = 5;
	x.vecinos = malloc((x.capacidad_v)*sizeof(VerticeP));


    return(x);
}


//Funcion para agregar un vertice al grafo
//Usado en la construccion de un grafo
VerticeP AgregarVertice(Grafo G, u32 z){
    VerticeP xPuntero = NULL; // puntero al vertice
    u32 n = G-> cantVertices; 
    u32 id_z = z % n;
    u32 contador = 0;

    //Revisamos si existe el vertice z 
    //si no exite, le encontramos lugar

    while (G->vertices_usados[id_z] && contador < n){
        contador++;

        if (G->vertices[id_z].nombreV == z){
            xPuntero = &G->vertices[id_z];
            contador = 0;
            break;
        }
        else{
            id_z++;
            if (id_z == n){
                id_z = 0;
            }
        }
    }

    if (contador == n){
        return NULL;
    }

    //En caso que no exista, se lo crea
    if (xPuntero == NULL){
        struct VerticeSt x = NuevoVertice(z);
        G->vertices[id_z] = x;
        xPuntero = &G->vertices[id_z];
        G->vertices_usados[id_z] = true;
        G->orden[id_z] = xPuntero;
    }

    return xPuntero;
}

void DestruirVertice(struct VerticeSt x){
    free(x.vecinos);
}


//Funcion para agregar un vecino a un vertice
//Usada en la construcion del grafo
void AgregarVecino(VerticeP x, VerticeP y){
    u32 grado = x->gradoV;

    //verificamos la capacidad asiganada al vertice para tener vecinos
    if (grado == x->capacidad_v){
        VerticeP *vecinos;
        vecinos = realloc(x->vecinos, (x->capacidad_v+5)*sizeof(VerticeP));
        //Si no tenemos espacio, pedimos mas
        x->capacidad_v += 5;
        x->vecinos = vecinos;
    }

    x->vecinos[x->gradoV] = y;
    x->gradoV++;
    //agregamos vecino y subimos us grado
}


//Funcion para comparar nombres de vertices
int CompName(const void * x, const void * y){
    VerticeP v1 = *(VerticeP*) x;
    VerticeP v2 = *(VerticeP*) y;

    //comparamos los vertices por su nombre
    if (v1->nombreV < v2->nombreV){
        return -1;
    }
    else{
        return 1;
    }
}


//Ordena los vertices del grafo en el orden natural 
//con respecto a sus nombre
void OrdenNatural(Grafo G){
    qsort(G->orden, G->cantVertices, sizeof(VerticeP), CompName);
    memcpy(G->orden_natural, G->orden, G->cantVertices*sizeof(VerticeP));
}

//Busca el vertice con mayor grado
u32 DeltaGrafo(Grafo G){
    u32 lados = G->cantVertices;
    u32 delta = 0;

    for (u32 i=0; i<lados; i++){
        if (G->vertices[i].gradoV > delta){
            delta = G->vertices[i].gradoV;
        }
    }

    return delta;
}



//Algoritmo de busqueda lineal
u32 encontrarPosVert_lineal(Grafo G, u32 our_vert_name){
    u32 cantidadV = G->cantVertices;
    u32 flag = 1;
    u32 posicion_encontrada = 0;
    u32 i = 0;

    while(i <cantidadV && flag){
        if (G->orden_natural[i]->nombreV == our_vert_name){
            posicion_encontrada = i;
            flag = 0;
        }
        i++;
    }

    return posicion_encontrada;
}


/* -----------------------------------------
----------------------------------------
--------------------------------------*/


