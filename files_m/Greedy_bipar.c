#include "AlduinPaarthurnaxIrileth.h"
#include "math.h"

#define MAX(a,b) (((a)>(b))?(a):(b))
#define ERROR_BAD (pow(2,32)-1)

/*--------------------------------------------------
-----------------------------------------------------
----------FUNCIONES AUXILIARES----------------------
---------------------------------------------------*/


//Funcion auxiliar pseudorandom
static unsigned int s = 1;

unsigned int pseudorandom(unsigned int seed) {
  seed += s << 4;
  seed *= 1103515245;
  seed += 12345;
  seed = (unsigned int) (seed / 65536) % 2048;

  return seed;
}

//Auxiliar para qsort- Ordena de mayor a menor
int cmpfunc (const void * a, const void * b) {
   return (*(int*)b -  *(int*)a );
}


//Auxiliar para qsort- ordena de menor a mayor
int cmpfunc1 (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}


/*--------------------------------------------------
-----------------------------------------------------
-----------------------------------------------------
---------------------------------------------------*/

//Funciones de coloreo

u32* Bipartito(Grafo G){
    u32 n_vert = NumeroDeVertices(G);

    //Reservamos el espacio para el array
    u32 *punt_array = malloc(sizeof(u32)*n_vert);

    // For para resetear los colores de los vertices
    for(u32 i = 0; i < n_vert; i++) {
        punt_array[i] = 0;
    }

    //Variable auxiliar que tiene el color que necesitamos
    u32 paint_color = 0;

    //Funcion de coloreo
    u32 indice = 0;
    while(indice < n_vert && paint_color != 3){
        if (punt_array[indice] == 0){
            punt_array[indice] = 1;
            paint_color = 2;
        }
        else if(punt_array[indice]==1){
            paint_color = 2;
        }
        else{ //este vertice tiene el color 2
            paint_color = 1;
        }

        for(u32 j=0; j< Grado(indice,G);j++){
            u32 xVec = IndiceONVecino(j,indice,G);

            if(xVec> n_vert){ //Implica que indice on vecino devolvio error
                paint_color = 3;
            }

            if (punt_array[xVec]==0){
                punt_array[xVec] = paint_color;
            }
            else if (punt_array[xVec] == paint_color){
                //si es del mismo color, necesitamos un nuevo color
                //por lo que no es bipartito
                paint_color = 3;
            }
            else{
                ; //si es de distinto color, no hago nada
            }
        }

        indice++;
    }

    if(paint_color != 3){
        return punt_array;
    }
    else{
        free(punt_array);
        return NULL;
    }
}




u32 Greedy(Grafo G,u32* Orden,u32* Coloreo){
    u32 n = NumeroDeVertices(G); //cant de vertices
    u32 color;                   //variables color actual del vecino
    u32 max_color = 0;           // Cant max de colores
    bool usado[n];              //Array con colores no disponibles
    u32 grado = 0;

    // Inicializo todos los colores en false(sin usar).
    memset(usado, false, (n)*sizeof(bool));

    //Coloreamos el primer vertice con 0
    Coloreo[Orden[0]] = 0;

    // Revisamos los vecinos del vertice u.
    // y flageamos los colores usados.
    for (u32 i = 1; i<n;i++){
        u32 vertActual = Orden[i];
        grado = Grado(vertActual,G);

        // For para recorrer los vecinos, donde chequeamos el color de cada uno de ellos
        // y marcamos el mismo como usado (siempre y cuando este coloreado).
        for(u32 j=0; j<grado; j++){
            u32 vecinoJ = IndiceONVecino(j,vertActual,G);
            color = Coloreo[vecinoJ];

            if(color){
                usado[color] = true;
            }
        }

        //Buscamos el primer color disponible
        for(u32 k = 1; k<n;k++){
            if(!usado[k]){
                Coloreo[vertActual] = k;
                max_color = MAX(max_color,k);
                break;
            }
        }

        // Reseteamos el array de colores disponibles a falso
        for(u32 l=0; l<grado; l++){
            u32 vecinol = IndiceONVecino(l,vertActual,G);
            color = Coloreo[vecinol];

            if(color){
                usado[color] = false;
            }
        }
    }

    if (max_color>n){
        //Esto no deberia poder pasar salvo algun error
        return ERROR_BAD;
    }else{
        return max_color;
    }
}



//Ordenamiento a partir de claves
char OrdenFromKey(u32 n,u32* key,u32* Orden){

    //For para rellenar el arreglo
    for(u32 indice=0;indice<n;indice++){
        Orden[indice] = key[indice];
    }

    //Ordenamos de mayor a menor
    qsort(Orden, n, sizeof(u32), cmpfunc);

    return ('0');
}



//Aleatorizar Keys
void AleatorizarKeys(u32 n,u32 R,u32* key){
    u32 random,tmp;

    for(u32 i=0; i<n;i++){
        random = pseudorandom(R) % n;
        tmp = key[i];
        key[i] = key[random];
        key[random] = tmp;
    }  
}


//permutadores de colores
u32* PermutarColores(u32 n,u32* Coloreo,u32 R){

    u32 max_color = Coloreo[0];

    for (u32 i=1; i<n; i++){
        if (Coloreo[i]>max_color){
            max_color = Coloreo[i];
        }
    }

    u32 r = max_color +1;

    //Reservamos el espacio para el array auxiliar
    u32 *punt_array = malloc(sizeof(u32)*n);
    if(punt_array == NULL){
        return NULL;
    }

    //Llenamos el arreglo auxiliar
    for (u32 i=0; i<r; i++){
        punt_array[i] = i;
    }

    AleatorizarKeys(r,R,punt_array);


    u32 *ColoreoNuevo = malloc(sizeof(u32)*n);
    if(ColoreoNuevo == NULL){
        return NULL;
    }

    for (u32 j=0; j<n; j++){
        ColoreoNuevo[j] = punt_array[Coloreo[j]];
    }
    free(punt_array);

    return ColoreoNuevo;
}


u32* RecoloreoCardinalidadDecrecienteBC(u32 n,u32* Coloreo){

    //Reservamos el espacio para el array auxiliar
    u32 *punt_array = malloc(sizeof(u32)*n);
    if(punt_array == NULL){
        return NULL;
    }

    
    for (u32 i=0; i<n; i++){
        punt_array[i] = Coloreo[i]; 
    }

    qsort(punt_array, n, sizeof(u32), cmpfunc);

    return punt_array;
}


