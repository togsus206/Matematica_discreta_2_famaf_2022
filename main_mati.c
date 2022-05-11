#include <stdio.h>
#include <stdlib.h>

#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "AlduinPaarthurnaxIrileth.h"

int main(){
    Grafo grafito = ConstruccionDelGrafo();

    /*
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
    */
    

    
    u32 cant_v = NumeroDeVertices(grafito);

    u32 *elcoloreo = malloc(sizeof(u32)*cant_v);
    u32 *elorden = malloc(sizeof(u32)*cant_v);
    u32 *elorden2 = malloc(sizeof(u32)*cant_v);

    for (u32 i=0; i <cant_v; i++){
        elorden[i] = i;
        elorden2[i] = cant_v-i;
    }

    u32 *elorden3 = malloc(sizeof(u32)*cant_v);
    char c = OrdenFromKey(cant_v,elorden,elorden3);

    AleatorizarKeys(cant_v, 60000,elorden3);

    u32 elcolor = Greedy(grafito, elorden2,elcoloreo);
    u32 elcolor2 = Greedy(grafito,elorden3,elcoloreo);

    printf("El coloreo es de %u colores\n", elcolor);
    if (c == '0'){
        printf("El coloreo es de %u colores\n", elcolor2);
    }
    
    
}
