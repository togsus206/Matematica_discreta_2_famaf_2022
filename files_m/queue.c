#include "queue.h"

struct QueueSt CrearQueue(u32 size) {
    struct QueueSt q;
    q.head = q.tail = -1;
    q.theQueue = malloc(size*sizeof(u32));
    return q;
}

void DestruirQueue(struct QueueSt *q) {
    free(q->theQueue);
}

void Enqueue(struct QueueSt *q, u32 v) {
    // Increment tail index
    q->tail++;
    // Add the item to the Queue
    q->theQueue[q->tail] = v;
    return;
}

u32 Dequeue(struct QueueSt *q) {
    u32 v;
    q->head++;
    v = q->theQueue[q->head]; // Get character to return
    return v;           // Return popped character
}

u32 isEmpty(struct QueueSt *q) {
    return (q->head == q->tail);
}