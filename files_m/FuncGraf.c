#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "FuncExtra.h"
#include "math.h"

#define ERROR_BAD (pow(2,32)-1)

//Funciones de construccion y destruccion del grafo
/////////////////////////////////////////////////////


Grafo ConstruccionDelGrafo(){
    //cantv = cantidad de vertices
    //cantl = cantidad de lados
    u32 cantv, cantl;

    int buffsize = 80; //largo de las lineas
    char input[buffsize]; //Lugar de las lineas del input

    input[0] = 'c';
    while (input[0] == 'c'){
        // Se piden lineas hasta que no sean mas comentarios(alias "C")
        if(fgets(input, buffsize, stdin) == NULL) {
            printf("Error de estructura");
            return NULL;
        }
    }


    // Nos aseguramos que siga la letra "p"
    if (input[0] != 'p') {
        printf("Formato de entrada invalido\n");
        return NULL;
    }
    char p = 'o';
    char edge[4];
    edge[0] = 'f';

    //Parseo de linea
    sscanf(input, "%c %s %u %u", &p, edge, &cantv, &cantl);

    //Chequeo del input
    if (strncmp(edge, "edge", 4) != 0) {
        printf("Formato de entrada invalido\n");
        return NULL;
    }

    if(cantv == 0 && cantl > 0) {
        printf("Formato de entrada invalido\n");
        return NULL;
    }

    //Comienza la construccionDelGrafo

    Grafo g = NULL; //creo el Grafo
    g = malloc(1*sizeof(struct GrafoSt)); //le asigno memoria

    g->cantVertices = cantv;
    g->cantLados = cantl;
    g->vertices = calloc(cantv, sizeof(struct VerticeSt));
    g->orden =  malloc(cantv*sizeof(VerticeP));
    g->orden_natural = calloc(cantv, sizeof(VerticeP));
    g->vertices_usados = calloc(cantv, sizeof(bool));
    g->delta = 0;

    u32 n, m; 

    VerticeP xPuntero = NULL;
    VerticeP yPuntero = NULL;

    for (u32 i = 0; i<cantl;i++){
        //se leen los lados pidiendo lineas del tamaño del buffsize
        if(fgets(input, buffsize, stdin) != NULL){
            //Parseo Lados
            sscanf(input, "%c %u %u", &p, &n, &m);
            //si p es distinto de "e", la linea esta mal puesta
            if(p != 'e'){
                printf("Mal formato de lado\n");
                return NULL;
            }
            else{
                //se agrega el lados
                xPuntero = AgregarVertice(g,n);
                yPuntero = AgregarVertice(g,m);

                if (xPuntero != NULL){
                    AgregarVecino(xPuntero,yPuntero);
                }
                else{
                    printf("Error en la carga del lado\n");
                    return NULL;
                }

                if (yPuntero != NULL){
                    AgregarVecino(yPuntero,xPuntero);
                }
                else{
                    printf("Error en la carga del lado\n");
                    return NULL;
                }
            }
        }
        else{
            printf("Formato de entrada invalido\n");
            return NULL;
        }
    }

    //Completamos la estructura con el orden natural de los vertices
    OrdenNatural(g); 

    //LLenamos el campo "posi_in_ordNat" 
    for (u32 i = 0; i < g->cantVertices; i++){
        g->orden_natural[i]->posi_in_ordNat = i;
    }
    
    //Calculamos el delta
    g->delta = DeltaGrafo(g);

    //Retornamos el grafo creado
    return g;
}



void DestruccionDelGrafo(Grafo G){
    //Primero se liberan los vertices y finalmente se libera G
    for (u32 i =0; i<G->cantVertices;i++){
        DestruirVertice(G->vertices[i]);
    }

    free(G->vertices);
    free(G->orden);
    free(G->vertices_usados);
    free(G->orden_natural);
    free(G);
}


//Funciones para extraer informacion del grafoSt
/////////////////////////////////////////////////////


u32 NumeroDeVertices(Grafo G) {
    return G->cantVertices;
}

u32 NumeroDeLados(Grafo G) {
    return G->cantLados;
}


u32 Delta(Grafo G){
    return G->delta;
}


//Funciones para extraer datos de los vertices
///////////////////////////////////////////////////

u32 Nombre(u32 i,Grafo G){
    return G->orden_natural[i]->nombreV;
}


u32 Grado(u32 i,Grafo G){
    if (i >= G-> cantVertices){
        return ERROR_BAD;
    }
    else{
        return G->orden_natural[i]->gradoV;
    }
}

u32 IndiceONVecino(u32 j,u32 k,Grafo G){
    u32 n_vert = G->cantVertices;
    if ((k < n_vert) && (j < G->orden_natural[k]->gradoV)){
        u32 posi_vert = G->orden_natural[k]->vecinos[j]->posi_in_ordNat;

        return posi_vert;

    }
    else{
        return ERROR_BAD;
    }
}


