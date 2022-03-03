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

void initGraphVertex(GraphVertex* p_graph_vertex, size_t id);
void freeGraphVertex(GraphVertex* p_graph_vertex);

void initGraph(Graph* p_graph);
void freeGraph(Graph* p_graph);

GraphVertex* addVertex (Graph* p_graph, size_t id);
void removeVertex	   (Graph* p_graph, size_t id);
int hasVertex		   (Graph* p_graph, size_t id);
GraphVertex* getVertex (Graph* p_graph, size_t id);

void addEdge(Graph* p_graph,
			 size_t head_id,
			 size_t tail_id,
			 double weight);

void removeEdge(GraphVertex* p_tail_vertex, 
			 	GraphVertex* p_head_vertex);

int hasEdge(GraphVertex* p_tail_vertex,
			GraphVertex* p_head_vertex);

double getEdgeWeight(GraphVertex* p_tail_vertex,
					 GraphVertex* p_head_vertex);

#endif // COM_GITHUB_CODERODDE_PERL_GRAPH_H