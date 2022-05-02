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

    if (bipart != NULL){
        printf("El grafo es bipartito\n");
    }
    else{
        printf("El grafo no es bipartito\n");
    }

    return 1;
}
