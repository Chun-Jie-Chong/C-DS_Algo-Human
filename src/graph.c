//The Algorithms

// Graph ADT
// Adjacency Matrix Representation
#include "graph.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct GraphRep
{
    int **edges;  // adjacency matrix
    int nV;       // #vertices
    int nE;       // #edges
} GraphRep;

Graph newGraph(int V)
{
    assert(V >= 0);
    int i;

    Graph g = malloc(sizeof(GraphRep));
    assert(g != NULL);
    g->nV = V;
    g->nE = 0;

    // allocate memory for each row
    g->edges = malloc(V * sizeof(int *));
    assert(g->edges != NULL);
    // allocate memory for each column and initialise with 0
    for (i = 0; i < V; i++)
    {
        g->edges[i] = calloc(V, sizeof(int));
        assert(g->edges[i] != NULL);
    }

    return g;
}

// check if vertex is valid in a graph
bool validV(Graph g, Vertex v) { return (g != NULL && v >= 0 && v < g->nV); }

void insertEdge(Graph g, Edge e)
{
    assert(g != NULL && validV(g, e.v) && validV(g, e.w));

    if (!g->edges[e.v][e.w])
    {  // edge e not in graph
        g->edges[e.v][e.w] = 1;
        g->edges[e.w][e.v] = 1;
        g->nE++;
    }
}

void removeEdge(Graph g, Edge e)
{
    assert(g != NULL && validV(g, e.v) && validV(g, e.w));

    if (g->edges[e.v][e.w])
    {  // edge e in graph
        g->edges[e.v][e.w] = 0;
        g->edges[e.w][e.v] = 0;
        g->nE--;
    }
}

bool adjacent(Graph g, Vertex v, Vertex w)
{
    assert(g != NULL && validV(g, v) && validV(g, w));

    return (g->edges[v][w] != 0);
}

void showGraph(Graph g)
{
    assert(g != NULL);
    int i, j;

    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);
    for (i = 0; i < g->nV; i++)
        for (j = i + 1; j < g->nV; j++)
            if (g->edges[i][j])
                printf("Edge %d - %d\n", i, j);
}

void freeGraph(Graph g)
{
    assert(g != NULL);

    int i;
    for (i = 0; i < g->nV; i++) free(g->edges[i]);
    free(g->edges);
    free(g);
}

// int main(int argc, char *argv[]) {
//     if (argc < 2) {
//         fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
//         return EXIT_FAILURE;
//     }

//     FILE *file = fopen(argv[1], "r");
//     if (!file) {
//         perror("Could not open input file");
//         return EXIT_FAILURE;
//     }

//     int V;
//     if (fscanf(file, "%d", &V) == 1) { // Read number of vertices
//         Graph g = newGraph(V);

//         char command[10];
//         while (fscanf(file, "%s", command) != EOF) {
//             Edge e;
//             if (fscanf(file, "%d %d", &e.v, &e.w) == 2) { // Read edge vertices

//                 if (strcmp(command, "insert") == 0) {
//                     insertEdge(g, e);
//                 } else if (strcmp(command, "remove") == 0) {
//                     removeEdge(g, e);
//                 } else {
//                     fprintf(stderr, "Unknown command: %s\n", command);
//                 }
//             }
//         }
//         printf("Graph adjacency matrix:\n");
//         showGraph(g);
//         freeGraph(g);
//     }
//     fclose(file);

//     return EXIT_SUCCESS;
// }

// By
//  .----------------.  .----------------.  .----------------.
//  .-----------------.  .----------------.  .----------------.
// | .--------------. || .--------------. || .--------------. ||
// .--------------. | | .--------------. || .--------------. | | |  _________ |
// || | _____  _____ | || |      __      | || | ____  _____  | | | |  ____  ____
// | || |     ____     | | | | |  _   _  |  | || ||_   _||_   _|| || |     /  \
// | || ||_   \|_   _| | | | | |_   ||   _| | || |   .'    `.   | | | | |_/ | |
// \_|  | || |  | |    | |  | || |    / /\ \    | || |  |   \ | |   | | | |   |
// |__| |   | || |  /  .--.  \  | | | |     | |      | || |  | '    ' |  | || |
// / ____ \   | || |  | |\ \| |   | | | |   |  __  |   | || |  | |    | |  | |
// | |    _| |_     | || |   \ `--' /   | || | _/ /    \ \_ | || | _| |_\   |_
// | | | |  _| |  | |_  | || |  \  `--'  /  | | | |   |_____|    | || | `.__.'
// | || ||____|  |____|| || ||_____|\____| | | | | |____||____| | || | `.____.'
// | | | |              | || |              | || |              | || | | | | |
// | || |              | | | '--------------' || '--------------' ||
// '--------------' || '--------------' | | '--------------' || '--------------'
// |
//  '----------------'  '----------------'  '----------------'
//  '----------------'   '----------------'  '----------------'

//  Email :    z5261243@unsw.edu.au
//             hhoanhtuann@gmail.com