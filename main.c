#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

static const size_t NODES = 1000;
static const size_t EDGES = 6000;

double randfrom(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

Graph* buildGraph() {
    Graph* p_graph = malloc(sizeof(Graph));
    size_t id1;
    size_t id2;
    double weight;

    srand((unsigned) time(NULL));

    for (size_t id = 0; id < NODES; ++id) 
    {
        addVertex(p_graph, id);
    }

    for (size_t edge = 0; edge < EDGES; ++edge) 
    {
        id1 = rand() % NODES;
        id2 = rand() % NODES;
        weight = randfrom(0.0, 10.0);
        addEdge(p_graph, id1, id2, weight);
    }

    return p_graph; 
}

int main(int argc, char* argv[]) 
{
    Graph* p_graph = buildGraph();

    freeGraph(p_graph);
    return 0;
}
