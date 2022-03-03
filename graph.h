#ifndef COM_GITHUB_CODERODDE_PERL_GRAPH_H
#define COM_GITHUB_CODERODDE_PERL_GRAPH_H

#include "hash_map.h"

typedef struct GraphVertex {
	size_t id;
	WeightHashMap children;
	WeightHashMap parents;
} GraphVertex;

typedef struct Graph {
	HashMap nodes;
} Graph;

void addVertex		(Graph* p_graph, GraphVertex* p_vertex);
void removeVertex	(Graph* p_graph, GraphVertex* p_vertex);
int hasVertex		(Graph* p_graph, GraphVertex* p_vertex);

void addEdge(GraphVertex* p_tail_vertex, 
			 GraphVertex* p_head_vertex,
			 double weight);

void removeEdge(GraphVertex* p_tail_vertex, 
			 	GraphVertex* p_head_vertex);

int hasEdge(GraphVertex* p_tail_vertex,
			GraphVertex* p_head_vertex);

double getEdgeWeight(GraphVertex* p_tail_vertex,
					 GraphVertex* p_head_vertex);

#endif // COM_GITHUB_CODERODDE_PERL_GRAPH_H