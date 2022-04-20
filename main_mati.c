#include <stdio.h>
#include <stdlib.h>

#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

int main(){
    Grafo grafito = ConstruccionDelGrafo();

    
    if (grafito == NULL) {
        printf("Error en formato de entrada\n");
        return (EXIT_FAILURE);
    }
    
    printf("El delta de grafo: %u\n", grafito->delta);

    u32 veremos = IndiceONVecino(3,5,grafito);
    printf("%u", veremos);
    return 1;
}