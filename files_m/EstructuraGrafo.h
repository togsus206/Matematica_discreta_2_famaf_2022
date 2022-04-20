#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned int u32;

typedef struct VerticeSt *VerticeP;

typedef struct GrafoSt *Grafo;

struct VerticeSt {
    u32 nombreV;
    u32 gradoV;
    u32 colorV;
    u32 capacidad_v; //cantidad de vecinos que puede tener
    VerticeP *vecinos;
    u32 hashV;
    u32 posi_in_ordNat; //posicion del vertice en el orden natural
};

struct GrafoSt {
    u32 cantVertices;
    u32 cantLados;
    u32 cantcolor;
    u32 delta;
    struct VerticeSt *vertices;
    VerticeP *orden; // arreglo con el orden de los vertices
    VerticeP *orden_natural; //arreglo con el orden natural
    bool *vertices_usados; //arreglo para saber si ya se creo el vertice
    
};
