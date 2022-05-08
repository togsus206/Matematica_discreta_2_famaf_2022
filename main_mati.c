#include <stdio.h>
#include <stdlib.h>

#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "AlduinPaarthurnaxIrileth.h"

int main(){
    Grafo grafito = ConstruccionDelGrafo();

    
    if (grafito == NULL) {
        printf("Error en formato de entrada\n");
        return (EXIT_FAILURE);
    }
    
    
    u32 *bipart = Bipartito(grafito);

    if (bipart == NULL){
        printf("El grafo no es bipartito\n");
    }
    else{
        printf("El grafo es bipartito\n");
    }
    

    /*
    u32 cant_v = NumeroDeVertices(grafito);

    u32 *elcoloreo = malloc(sizeof(u32)*cant_v);
    u32 *elorden = malloc(sizeof(u32)*cant_v);

    for (u32 i=0; i <cant_v; i++){
        //elorden[i] = i;
        elorden[i] = cant_v-i;
    }

    u32 elcolor = Greedy(grafito, elorden,elcoloreo);

    printf("El coloreo es de %u colores\n", elcolor);
    */
    
}
