#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

// List Function Prototypes
struct QueueSt {
    int head;
    int tail;
    u32 *theQueue;
};

struct QueueSt CrearQueue(u32 size);          // Initialize the queue

void DestruirQueue(struct QueueSt *q);       // Remove all items from the queue

void Enqueue(struct QueueSt *q, u32 v);     // Enter an item in the queue

u32 Dequeue(struct QueueSt *q);         // Remove an item from the queue

u32 isEmpty(struct QueueSt *q);             // Return true if queue is empty
