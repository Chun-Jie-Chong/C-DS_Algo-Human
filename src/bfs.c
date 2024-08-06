// The Algorithms

#include <stdbool.h>
#include <stdio.h>
#include "graph.c"
#include <assert.h>
#include <stdlib.h>

typedef struct QueueRep *queue;

queue newQueue();               // set up empty queue
void dropQueue(queue);          // remove unwanted queue
int QueueIsEmpty(queue);        // check whether queue is empty
void QueueEnqueue(queue, int);  // insert an int at end of queue
int QueueDequeue(queue);        // remove int from front of queue


// Queue ADT implementation ... COMP2521
typedef struct node
{
    int data;
    struct node *next;
} NodeT;

typedef struct QueueRep
{
    int length;
    NodeT *head;
    NodeT *tail;
} QueueRep;

#define MAX_NODES 1000

int visited[MAX_NODES];  // array to store visiting order
                         // indexed by vertex 0..nV-1

// set up empty queue
queue newQueue()
{
    queue Q = malloc(sizeof(QueueRep));
    Q->length = 0;
    Q->head = NULL;
    Q->tail = NULL;
    return Q;
}

// remove unwanted queue
void dropQueue(queue Q)
{
    NodeT *curr = Q->head;
    while (curr != NULL)
    {
        NodeT *temp = curr->next;
        free(curr);
        curr = temp;
    }
    free(Q);
}

// check whether queue is empty
int QueueIsEmpty(queue Q) { return (Q->length == 0); }

// insert an int at end of queue
void QueueEnqueue(queue Q, int v)
{
    NodeT *new = malloc(sizeof(NodeT));
    assert(new != NULL);
    new->data = v;
    new->next = NULL;
    if (Q->tail != NULL)
    {
        Q->tail->next = new;
        Q->tail = new;
    }
    else
    {
        Q->head = new;
        Q->tail = new;
    }
    Q->length++;
}

// remove int from front of queue
int QueueDequeue(queue Q)
{
    assert(Q->length > 0);
    NodeT *p = Q->head;
    Q->head = Q->head->next;
    if (Q->head == NULL)
    {
        Q->tail = NULL;
    }
    Q->length--;
    int d = p->data;
    free(p);
    return d;
}

bool bfs(Graph g, int nV, Vertex src, Vertex dest)
{
    Vertex v;
    for (v = 0; v < nV; v++) visited[v] = -1;

    visited[src] = src;
    queue Q = newQueue();
    QueueEnqueue(Q, src);
    while (!QueueIsEmpty(Q))
    {
        v = QueueDequeue(Q);
        Vertex w;
        for (w = 0; w < nV; w++)
            if (adjacent(g, v, w) && visited[w] == -1)
            {
                visited[w] = v;
                if (w == dest)
                    return true;
                else
                    QueueEnqueue(Q, w);
            }
    }
    return false;
}

// int main(void)
// {
//     int V = 10;
//     Graph g = newGraph(V);

//     Edge e;
//     e.v = 0;
//     e.w = 1;
//     insertEdge(g, e);
//     e.v = 0;
//     e.w = 2;
//     insertEdge(g, e);
//     e.v = 0;
//     e.w = 5;
//     insertEdge(g, e);
//     e.v = 1;
//     e.w = 5;
//     insertEdge(g, e);
//     e.v = 2;
//     e.w = 3;
//     insertEdge(g, e);
//     e.v = 3;
//     e.w = 4;
//     insertEdge(g, e);
//     e.v = 3;
//     e.w = 5;
//     insertEdge(g, e);
//     e.v = 3;
//     e.w = 8;
//     insertEdge(g, e);
//     e.v = 4;
//     e.w = 5;
//     insertEdge(g, e);
//     e.v = 4;
//     e.w = 7;
//     insertEdge(g, e);
//     e.v = 4;
//     e.w = 8;
//     insertEdge(g, e);
//     e.v = 5;
//     e.w = 6;
//     insertEdge(g, e);
//     e.v = 7;
//     e.w = 8;
//     insertEdge(g, e);
//     e.v = 7;
//     e.w = 9;
//     insertEdge(g, e);
//     e.v = 8;
//     e.w = 9;
//     insertEdge(g, e);

//     int src = 0, dest = 6;
//     if (bfs(g, V, src, dest))
//     {
//         Vertex v = dest;
//         while (v != src)
//         {
//             printf("%d - ", v);
//             v = visited[v];
//         }
//         printf("%d\n", src);
//     }
//     return 0;
// }
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    int V;
    if (fscanf(file, "%d", &V) == 1) {
        Graph g = newGraph(V);

        int src, dest;
        if (fscanf(file, "%d %d", &src, &dest) == 2) {
            Edge edge;
            while (fscanf(file, "%d %d", &edge.v, &edge.w) == 2) {
                insertEdge(g, edge);
            }
            printf("Graph adjacency matrix:\n");
            showGraph(g);

            if (bfs(g, V, src, dest)) {
                printf("\nThere is a path from %d to %d\n", src, dest);
            } else {
                printf("\nThere is no path from %d to %d\n", src, dest);
            }

            freeGraph(g);
        }
    }
    fclose(file);
    return 0;
}