#include "graph.h"

static size_t hash_function(void* id) 
{
	return id;
}

static bool equals_function(void* a, void* b) 
{
	size_t sza = (size_t) a;
	size_t szb = (size_t) b;
	return sza == szb;
}

static const size_t initial_capacity = 1024;
static const float load_factor = 1.3f;

void initGraphVertex(GraphVertex* p_graph_vertex)
{
	p_graph_vertex->p_children = 
		unordered_map_alloc(initial_capacity,
							load_factor,
							hash_function,
							equals_function);

	p_graph_vertex->p_parents = 
		unordered_map_alloc(initial_capacity,
							load_factor,
							hash_function,
							equals_function);
}

void freeGraphVertex(GraphVertex* p_graph_vertex) 
{
	unordered_map_free(p_graph_vertex->p_children);
	unordered_map_free(p_graph_vertex->p_parents);
}

void initGraph(Graph* p_graph)
{
	p_graph->p_nodes = 
		unordered_map_alloc(
			initial_capacity,
			load_factor,
			hash_function,
			equals_function);
}

void freeGraph(Graph* p_graph) 
{
	unordered_map_iterator* p_iterator =
		unordered_map_iterator_alloc(p_graph->p_nodes);

	while (unordered_map_iterator_has_next(p_iterator)) 
	{
		void** pp_key;
		void** pp_value;

		unordered_map_iterator_next(
			p_iterator,
			pp_key, 
			pp_value);

		unordered_map* p_graph_vertex = *pp_value;
		freeGraphVertex(p_graph_vertex);
	}

	unordered_map_free(p_graph->p_nodes);
	p_graph->p_nodes = NULL;
}

void addVertex(Graph* p_graph, GraphVertex* p_vertex) 
{
	if (!unordered_map_get(p_graph->p_nodes, p_vertex->id)) {
		GraphVertex* p_graph_vertex = 
			malloc(sizeof(GraphVertex));

		initGraphVertex(p_graph_vertex);

		unordered_map_put(p_graph->p_nodes, 
						  p_graph_vertex->id,
						  p_graph_vertex);
	}
}


void removeVertex(Graph* p_graph, GraphVertex* p_vertex)
{
	unordered_map_remove(p_graph->p_nodes,
						 p_vertex->id);
}

int hasVertex(Graph* p_graph, GraphVertex* p_vertex)
{
	return unordered_map_contains_key(p_graph->p_nodes, 
								      p_vertex->id);
}

void addEdge(Graph* p_graph,
			 GraphVertex* p_tail_vertex, 
			 GraphVertex* p_head_vertex,
			 double weight)
{
	if (!unordered_map_contains_key(p_graph->p_nodes,
									p_tail_vertex->id)) 
	{
		addVertex(p_graph, p_tail_vertex);
	}

	if (!unordered_map_contains_key(p_graph->p_nodes,
									p_head_vertex->id)) 
	{
		addVertex(p_graph, p_head_vertex);
	}

	double* p_weight = malloc(*p_weight);
	*p_weight = weight;

	unordered_map_put(p_tail_vertex->p_children, 
					  p_head_vertex->id,
					  (void*) p_weight);

	unordered_map_put(p_head_vertex->p_parents,
					  p_tail_vertex->id,
					  (void*) p_weight);
}

void removeEdge(GraphVertex* p_tail_vertex, 
			 	GraphVertex* p_head_vertex)
{
	unordered_map_remove(p_tail_vertex->p_children, 
						 p_head_vertex->id);

	unordered_map_remove(p_head_vertex->p_parents,
						 p_tail_vertex->id);
}

int hasEdge(GraphVertex* p_tail_vertex,
			GraphVertex* p_head_vertex)
{
	return unordered_map_contains_key(
				p_tail_vertex->p_children,
				p_head_vertex->id);
}

double getEdgeWeight(GraphVertex* p_tail_vertex,
					 GraphVertex* p_head_vertex)
{
	unordered_map* p_children_map = p_tail_vertex->p_children;

	void* p_value =  
	unordered_map_get(p_children_map, 
					  (void*)(p_head_vertex->id));

	double* p_weight = (double*)(p_value);
	return *p_weight;
}
