#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "AlduinPaarthurnaxIrileth.h"


int main(int argc, char *argv[]){

    //Construccion del grafo
    Grafo grafito = ConstruccionDelGrafo();

    //Revisamos que haya salido todo bien
    if (grafito == NULL) {
        printf("Error en formato de entrada\n");
        return (EXIT_FAILURE);
    }

    //Datos del grafo
    u32 num_vertices = NumeroDeVertices(grafito);
    u32 num_lados = NumeroDeLados(grafito);
    u32 Edelta = Delta(grafito);

    //Variable para saber cuantos Greedys hacemos
    u32 cant_Greddy = 0;

    printf("El numero de vertices del grafo es: %u\n", num_vertices);
    printf("El numero de lados del grafo es: %u\n", num_lados);
    printf("El delta del grafo es: %u\n", Edelta);
    printf("\n");

    //Verificacion de si el grafo es bipartito
    u32 *bipart = Bipartito(grafito);


    if (bipart == NULL){
        printf("El grafo no es bipartito\n\n");
    }
    else{
        printf("El grafo es bipartito\n\n");

        if (num_vertices < 101){
            printf("Vertices con el color 1: \n");
            for(u32 i=0; i<num_vertices; i++){
                if(bipart[i] == 1){
                    printf("%u--", Nombre(i,grafito));
                }
            }
            printf("\n\n");

            printf("Vertices pintados con el color 2: \n");
            for(u32 j=0; j<num_vertices; j++){
                if(bipart[j] == 2){
                    printf("%u--", Nombre(j,grafito));
                }
            }
            printf("\n\n");
        }

        return EXIT_SUCCESS;
    }

    //Obtenemos la variable de aleatoridad
    if (argc <4){
        printf("No se pudo obtener la variables aleatoridad\n");
    }
    u32 variable_aleatoria = atoi(argv[3]);

    u32 alfa = atoi(argv[1]);
    u32 beta = atoi(argv[2]);


    ///////////////////////////////////////////////////////////////
    //Obtencion de ordenes Y Greedys

    //orden Natural
    u32 *orden_nat = malloc(num_vertices*sizeof(u32));

    for (u32 i = 0; i < num_vertices; ++i){
        orden_nat[i] = i;
    }

    u32 *elcoloreo1 = malloc(sizeof(u32)*num_vertices);
    u32 greedy1 = Greedy(grafito,orden_nat,elcoloreo1);
    cant_Greddy++;
    printf("Greedy colorea el grafo en el orden natural con: %u colores\n", greedy1);


    //Orden Welsh-Powell
    u32 *OrdenWelshPowell = malloc(num_vertices*sizeof(u32));

    u32 *k = malloc(num_vertices*sizeof(u32));
    for (u32 i = 0; i < num_vertices; ++i){
        k[i]=Grado(i,grafito); 
    }
    char todo_ok = OrdenFromKey(num_vertices,k,OrdenWelshPowell);

    if (todo_ok == '1'){
        printf("Ocurrio un problema\n");
        return EXIT_FAILURE;
    }

    u32 *elcoloreo2 = malloc(sizeof(u32)*num_vertices);
    u32 greedy2 = Greedy(grafito, OrdenWelshPowell, elcoloreo2);
    cant_Greddy++;
    printf("Greedy colorea el grafo en el orden Welsh-Powell con: %u colores\n\n", greedy2);


    //RESTO ORDENES
    //Arreglo para guardar la cant de colores usados para cada permutacion.
    u32 *cant_color_ordenes = malloc(alfa*sizeof(u32));

    u32 *ordenes[alfa];
    for(u32 j=0; j<alfa;j++){
        ordenes[j] = (u32 *)malloc(num_vertices*sizeof(u32));
        u32 * aux = ordenes[j];
        for(u32 t=0; t<num_vertices; t++){
            aux[t] = t;
        }
    }

    u32 variable_aleat;
    u32 seed;
    for (u32 i=0; i<alfa; i++){
        seed = (u32) time(NULL)*10/5-2;
        variable_aleat = variable_aleatoria*(i*12)+seed*30;
        AleatorizarKeys(num_vertices,variable_aleat,ordenes[i]);

    }

    u32 *coloreos[alfa];
    for(u32 j=0; j<alfa; j++){
        coloreos[j] = (u32 *)malloc(num_vertices*sizeof(u32));
    }
    
    u32 greedy3;
    for (u32 k=0; k<alfa; k++){
        greedy3 = Greedy(grafito, ordenes[k], coloreos[k]);
        cant_color_ordenes[k] = greedy3;
        cant_Greddy++;
        printf("Greedy colorea el grafo en este orden con:%u colores\n\n", greedy3);
    } 
 
    //------------------------------------------------------------------------------//
    // 3XBeta coloreos
    printf("---------------------------Empezamos punto 6------------------------\n\n");

    //Array donde guardaremos el mejor coloreo para cada uno de los ordenes alfa
    u32 *Best_colors_for_each_alfa = malloc((alfa+2)*sizeof(u32));


    u32 *Mejor_coloreo_for_each[alfa];
    for(u32 j=0; j<alfa; j++){
        Mejor_coloreo_for_each[j] = (u32 *)malloc(num_vertices*sizeof(u32));
    }

    //Variables aleatorias
    seed = (u32) time(NULL);
    variable_aleat = variable_aleatoria+seed;


    //EMPEZAMOS CON LO QUE ERA EL ORDEN NATURAL
    printf("BetaX3 Ordenamientos con el orden natural\n\n");
    u32 *coloreo_anterior = elcoloreo1;
    Mejor_coloreo_for_each[0] = elcoloreo1;
    u32 greedy_ant = greedy1;

    u32 *elcoloreo3 = malloc(sizeof(u32)*num_vertices);
    u32 *elcoloreo4 = malloc(sizeof(u32)*num_vertices);
    u32 *elcoloreo5 = malloc(sizeof(u32)*num_vertices);

    for (u32 l=0; l<beta; l++){

        //Primer orden
        u32 *ordenColor1 = malloc(num_vertices*sizeof(u32));
        char all_good = OrdenFromKey(num_vertices,coloreo_anterior,ordenColor1);
        if (all_good == '1'){
            printf("Ocurrio un problema\n");
            return EXIT_FAILURE;
        }

        u32 nuevo_greedy = Greedy(grafito,ordenColor1,elcoloreo3);
        cant_Greddy++;

        printf("(1)Greedy colorea el grafo en este orden con: %u colores\n", nuevo_greedy);

        if (nuevo_greedy>greedy_ant){
            printf("Aumentaron los colores, por lo que se detuvo el proceso\n");
            return EXIT_SUCCESS;
        }
        greedy_ant = nuevo_greedy;
        coloreo_anterior = elcoloreo3;
        Mejor_coloreo_for_each[0] = ordenColor1;

        //Segundo orden
        seed = (u32) time(NULL);
        u32 *ordenColor2 = malloc(num_vertices*sizeof(u32));
        u32 *permutacion = PermutarColores(num_vertices,coloreo_anterior,variable_aleat+seed);
        char all_good2 = OrdenFromKey(num_vertices,permutacion,ordenColor2);
        if (all_good2 == '1'){
            printf("Ocurrio un problema\n");
            return EXIT_FAILURE;
        }
        
        u32 nuevo_greedy2 = Greedy(grafito,ordenColor2,elcoloreo4);
        cant_Greddy++;

        printf("(2)Greedy colorea el grafo en este orden con: %u colores\n", nuevo_greedy2);

        if (greedy_ant<nuevo_greedy2){
            printf("Aumentaron los colores, por lo que se detuvo el proceso\n");
            return EXIT_SUCCESS;
        }
        greedy_ant = nuevo_greedy2;
        Mejor_coloreo_for_each[0] = ordenColor2;
        coloreo_anterior = elcoloreo4;
        free(ordenColor1);


        //Tercer orden
        u32 *ordenColor3 = malloc(num_vertices*sizeof(u32));
        u32 *permutacion2 = RecoloreoCardinalidadDecrecienteBC(num_vertices,coloreo_anterior);
        char all_good3 = OrdenFromKey(num_vertices,permutacion2,ordenColor3);
        if (all_good3 == '1'){
            printf("Ocurrio un problema\n");
            return EXIT_FAILURE;
        }

        u32 nuevo_greedy3 = Greedy(grafito,ordenColor3,elcoloreo5);
        cant_Greddy++;

        printf("(3)Greedy colorea el grafo en este orden con: %u colores\n\n", nuevo_greedy3);

        if (greedy_ant<nuevo_greedy3){
            printf("Aumentaron los colores, por lo que se detuvo el proceso\n");
            return EXIT_SUCCESS;
        }
        greedy_ant = nuevo_greedy3;
        coloreo_anterior = elcoloreo5;
        Mejor_coloreo_for_each[0] = ordenColor3;
        free(ordenColor2);
        
    }

    Best_colors_for_each_alfa[0] = greedy_ant;

    //FIN ORDEN NATURAL



    //EMPEZAMOS CON EL ORDEN WELSH-POWELL

     //Variables aleatorias
    seed = (u32) time(NULL);
    variable_aleat = variable_aleatoria+seed;

    printf("BetaX3 Ordenamientos con el orden Welsh-Powell\n\n");
    coloreo_anterior = elcoloreo2;
    Mejor_coloreo_for_each[1] = elcoloreo2;
    greedy_ant = greedy2;

    for (u32 l=0; l<beta; l++){

        //Primer orden
        u32 *ordenColor1 = malloc(num_vertices*sizeof(u32));
        char all_good = OrdenFromKey(num_vertices,coloreo_anterior,ordenColor1);
        if (all_good == '1'){
            printf("Ocurrio un problema\n");
            return EXIT_FAILURE;
        }

        u32 nuevo_greedy = Greedy(grafito,ordenColor1,elcoloreo3);
        cant_Greddy++;

        printf("(1)Greedy colorea el grafo en este orden con: %u colores\n", nuevo_greedy);

        if (nuevo_greedy>greedy_ant){
            printf("Aumentaron los colores, por lo que se detuvo el proceso\n");
            return EXIT_SUCCESS;
        }
        greedy_ant = nuevo_greedy;
        coloreo_anterior = elcoloreo3;
        Mejor_coloreo_for_each[1] = ordenColor1;

        //Segundo orden
        seed = (u32) time(NULL);
        u32 *ordenColor2 = malloc(num_vertices*sizeof(u32));
        u32 *permutacion = PermutarColores(num_vertices,coloreo_anterior,variable_aleat+seed);
        char all_good2 = OrdenFromKey(num_vertices,permutacion,ordenColor2);
        if (all_good2 == '1'){
            printf("Ocurrio un problema\n");
            return EXIT_FAILURE;
        }
        
        u32 nuevo_greedy2 = Greedy(grafito,ordenColor2,elcoloreo4);
        cant_Greddy++;

        printf("(2)Greedy colorea el grafo en este orden con: %u colores\n", nuevo_greedy2);

        if (greedy_ant<nuevo_greedy2){
            printf("Aumentaron los colores, por lo que se detuvo el proceso\n");
            return EXIT_SUCCESS;
        }
        greedy_ant = nuevo_greedy2;
        coloreo_anterior = elcoloreo4;
        Mejor_coloreo_for_each[1] = ordenColor2;
        free(ordenColor1);


        //Tercer orden
        u32 *ordenColor3 = malloc(num_vertices*sizeof(u32));
        u32 *permutacion2 = RecoloreoCardinalidadDecrecienteBC(num_vertices,coloreo_anterior);
        char all_good3 = OrdenFromKey(num_vertices,permutacion2,ordenColor3);
        if (all_good3 == '1'){
            printf("Aumentaron los colores, por lo que se detuvo el proceso\n");
            return EXIT_FAILURE;
        }

        u32 nuevo_greedy3 = Greedy(grafito,ordenColor3,elcoloreo5);
        cant_Greddy++;

        printf("(3)Greedy colorea el grafo en este orden con: %u colores\n\n", nuevo_greedy3);

        if (greedy_ant<nuevo_greedy3){
            printf("Aumentaron los colores, por lo que se detuvo el proceso\n");
            return EXIT_SUCCESS;
        }
        greedy_ant = nuevo_greedy3;
        coloreo_anterior = elcoloreo5;
        Mejor_coloreo_for_each[1] = ordenColor3;
        free(ordenColor2);
        
    }

    Best_colors_for_each_alfa[1] = greedy_ant;


    //AHORA CON EL RESTO DE LOS ALFA ORDENES
    printf("BetaX3 Ordenamientos con el resto de los alfa\n\n");

    for(u32 k=0; k<alfa; k++){
        //Variables aleatorias
        seed = (u32) time(NULL);
        variable_aleat = variable_aleatoria+seed;

        coloreo_anterior = coloreos[k];
        Mejor_coloreo_for_each[k+2] = coloreo_anterior;
        greedy_ant = cant_color_ordenes[k];

        for (u32 l=0; l<beta; l++){

            //Primer orden
            u32 *ordenColor1 = malloc(num_vertices*sizeof(u32));
            char all_good = OrdenFromKey(num_vertices,coloreo_anterior,ordenColor1);
            if (all_good == '1'){
                printf("Ocurrio un problema\n");
                return EXIT_FAILURE;
            }

            u32 nuevo_greedy = Greedy(grafito,ordenColor1,elcoloreo3);
            cant_Greddy++;

            printf("(1)Greedy colorea el grafo en este orden con: %u colores\n", nuevo_greedy);

            if (nuevo_greedy>greedy_ant){
                printf("Aumentaron los colores, por lo que se detuvo el proceso\n");
                return EXIT_SUCCESS;
            }
            greedy_ant = nuevo_greedy;
            coloreo_anterior = elcoloreo3;
            Mejor_coloreo_for_each[k+2] = ordenColor1;

            //Segundo orden
            seed = (u32) time(NULL);
            u32 *ordenColor2 = malloc(num_vertices*sizeof(u32));
            u32 *permutacion = PermutarColores(num_vertices,coloreo_anterior,variable_aleat+seed);
            char all_good2 = OrdenFromKey(num_vertices,permutacion,ordenColor2);
            if (all_good2 == '1'){
                printf("Ocurrio un problema\n");
                return EXIT_FAILURE;
            }
        
            u32 nuevo_greedy2 = Greedy(grafito,ordenColor2,elcoloreo4);
            cant_Greddy++;

            printf("(2)Greedy colorea el grafo en este orden con: %u colores\n", nuevo_greedy2);

            if (greedy_ant<nuevo_greedy2){
                printf("Aumentaron los colores, por lo que se detuvo el proceso\n");
                return EXIT_SUCCESS;
            }
            greedy_ant = nuevo_greedy2;
            coloreo_anterior = elcoloreo4;
            Mejor_coloreo_for_each[k+2] = ordenColor2;
            free(ordenColor1);


            //Tercer orden
            u32 *ordenColor3 = malloc(num_vertices*sizeof(u32));
            u32 *permutacion2 = RecoloreoCardinalidadDecrecienteBC(num_vertices,coloreo_anterior);
            char all_good3 = OrdenFromKey(num_vertices,permutacion2,ordenColor3);
            if (all_good3 == '1'){
                printf("Aumentaron los colores, por lo que se detuvo el proceso\n");
                return EXIT_FAILURE;
            }

            u32 nuevo_greedy3 = Greedy(grafito,ordenColor3,elcoloreo5);
            cant_Greddy++;

            printf("(3)Greedy colorea el grafo en este orden con: %u colores\n\n", nuevo_greedy3);

            if (greedy_ant<nuevo_greedy3){
                printf("Aumentaron los colores, por lo que se detuvo el proceso\n");
                return EXIT_SUCCESS;
            }
            greedy_ant = nuevo_greedy3;
            coloreo_anterior = elcoloreo5;
            Mejor_coloreo_for_each[k+2] = ordenColor3;
            free(ordenColor2);
        }
        Best_colors_for_each_alfa[k+2] = greedy_ant;

    }

    u32 menor_coloreo = Best_colors_for_each_alfa[0];
    //u32 *el_coloreo_del_menor = Mejor_coloreo_for_each[0];
    for (u32 i=0; i<alfa; i++){
        if (Best_colors_for_each_alfa[i]<menor_coloreo){
            menor_coloreo = Best_colors_for_each_alfa[i];
            //el_coloreo_del_menor = Mejor_coloreo_for_each[i];
        }
    }

    //Imprimo la cantidad de Greedy's hechos durante el programa
    printf("La cantidad de algoritmos Greedy hechos a traves de todo el trabajo fue de %u\n\n",cant_Greddy);
    printf("El menor numero con el que se ha logrado colorear el grafo es: %u\n", menor_coloreo);

    // printf("%u\n",Best_colors_for_each_alfa[0]);
    // printf("%u\n",Best_colors_for_each_alfa[1]);
    // printf("%u\n",Best_colors_for_each_alfa[2]);
    // printf("%u\n",Best_colors_for_each_alfa[3]);


    /*-------------------------------------------------------------
    ------Liberacion de memoria------------------------------------
    ---------------------------------------------------------------*/

    free(orden_nat);
    free(k);
    free(elcoloreo1);
    free(elcoloreo2);
    free(elcoloreo3);
    free(elcoloreo4);
    free(elcoloreo5);
    free(cant_color_ordenes);
    free(Best_colors_for_each_alfa);
    

    for(u32 j=0; j<alfa; j++){
        free(coloreos[j]);
    }

    for(u32 j=0; j<alfa; j++){
        free(ordenes[j]);
    }

    for(u32 j=0; j<alfa; j++){
        free(Mejor_coloreo_for_each[j]);
    }

    DestruccionDelGrafo(grafito);


}