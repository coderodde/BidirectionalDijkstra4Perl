#ifndef COM_GITHUB_CODERODDE_PERL_GRAPH_H
#define COM_GITHUB_CODERODDE_PERL_GRAPH_H

#include "unordered_map.h"

typedef struct GraphVertex {
	size_t id;
	unordered_map* p_children; // Maps a child to the edge weight.
	unordered_map* p_parents;  // Maps a parent to the edge weight.
} GraphVertex;

typedef struct Graph {
	// Maps each node ID to a vertex:
	unordered_map* p_nodes;
} Graph;

void initGraphVertex(GraphVertex* p_graph_vertex);
void freeGraphVertex(GraphVertex* p_graph_vertex);

void initGraph(Graph* p_graph);
void freeGraph(Graph* p_graph);

void addVertex		(Graph* p_graph, GraphVertex* p_vertex);
void removeVertex	(Graph* p_graph, GraphVertex* p_vertex);
int hasVertex		(Graph* p_graph, GraphVertex* p_vertex);

void addEdge(Graph* p_graph,
			 GraphVertex* p_tail_vertex, 
			 GraphVertex* p_head_vertex,
			 double weight);

void removeEdge(GraphVertex* p_tail_vertex, 
			 	GraphVertex* p_head_vertex);

int hasEdge(GraphVertex* p_tail_vertex,
			GraphVertex* p_head_vertex);

double getEdgeWeight(GraphVertex* p_tail_vertex,
					 GraphVertex* p_head_vertex);

#endif // COM_GITHUB_CODERODDE_PERL_GRAPH_H