//The Algorithms
#include <stdbool.h>
#include <stdio.h>
#include "graph.c"
#include <string.h>

#define MAX_NODES 1000

int visited[MAX_NODES];  // array to store visiting order
                         // indexed by vertex 0..nV-1

bool dfsPathCheck(Graph g, int nV, Vertex v, Vertex dest)
{
    Vertex w;
    for (w = 0; w < nV; w++)
        if (adjacent(g, v, w) && visited[w] == -1)
        {
            visited[w] = v;
            if (w == dest)
                return true;
            else if (dfsPathCheck(g, nV, w, dest))
                return true;
        }
    return false;
}

bool dfs(Graph g, int nV, Vertex src, Vertex dest)
{
    Vertex v;
    for (v = 0; v < nV; v++) visited[v] = -1;
    visited[src] = src;
    return dfsPathCheck(g, nV, src, dest);
}

// int main(void)
// {
//     int V = 6;
//     Graph g = newGraph(V);

//     Edge e;
//     e.v = 0;
//     e.w = 1;
//     insertEdge(g, e);
//     e.v = 0;
//     e.w = 4;
//     insertEdge(g, e);
//     e.v = 0;
//     e.w = 5;
//     insertEdge(g, e);
//     e.v = 5;
//     e.w = 4;
//     insertEdge(g, e);
//     e.v = 4;
//     e.w = 2;
//     insertEdge(g, e);
//     e.v = 4;
//     e.w = 3;
//     insertEdge(g, e);
//     e.v = 5;
//     e.w = 3;
//     insertEdge(g, e);
//     e.v = 1;
//     e.w = 2;
//     insertEdge(g, e);
//     e.v = 3;
//     e.w = 2;
//     insertEdge(g, e);

//     int src = 0, dest = 5;
//     if (dfs(g, V, src, dest))
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

            if (dfs(g, V, src, dest)) {
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