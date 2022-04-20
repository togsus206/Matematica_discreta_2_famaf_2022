#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

struct VerticeSt NuevoVertice(u32 n);

VerticeP AgregarVertice(Grafo G, u32 z);

void AgregarVecino(VerticeP x, VerticeP y);

int CompName(const void * x, const void * y);

void OrdenNatural(Grafo G);

u32 DeltaGrafo(Grafo G);

void DestruirVertice(struct VerticeSt x);

//u32 encontrarPosVert(Grafo G,u32 our_vert_name);

u32 encontrarPosVert_lineal(Grafo G, u32 our_vert_name);