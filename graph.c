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

void initGraphVertex(GraphVertex* p_graph_vertex, size_t id)
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

	p_graph_vertex->id = id;
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

	GraphVertex* p_graph_vertex;

	while (unordered_map_iterator_has_next(p_iterator)) 
	{
		void** pp_key;
		void** pp_value;

		unordered_map_iterator_next(
			p_iterator,
			pp_key, 
			pp_value);

		p_graph_vertex = *pp_value;
		freeGraphVertex(p_graph_vertex);
	}

	unordered_map_free(p_graph->p_nodes);
	p_graph->p_nodes = NULL;
}

GraphVertex* addVertex(Graph* p_graph, size_t id) 
{
	GraphVertex* p_graph_vertex = 
		unordered_map_get(p_graph->p_nodes, id);

	if (p_graph_vertex)
	{
		return p_graph_vertex;
	}

	p_graph_vertex = malloc(sizeof(GraphVertex));

	initGraphVertex(p_graph_vertex, id);

	unordered_map_put(p_graph->p_nodes, 
					  p_graph_vertex->id,
					  p_graph_vertex);

	return p_graph_vertex;
}

void removeVertex(Graph* p_graph, size_t id)
{
	GraphVertex* p_graph_vertex;
	GraphVertex* p_child;
	GraphVertex* p_parent;

	unordered_map_iterator* p_child_iterator;
	unordered_map_iterator* p_parent_iterator;

	double* p_weight;


	p_graph_vertex = unordered_map_get(p_graph->p_nodes, id);

	if (!p_graph_vertex) {
		return;
	}

	p_child_iterator = 
		unordered_map_iterator_alloc(p_graph_vertex->p_children);

	// Disconnect from children:
	while (unordered_map_iterator_has_next(p_child_iterator)) 
	{
		unordered_map_iterator_next(p_child_iterator,
									&p_child,
									&p_weight);

		removeEdge(p_graph_vertex, p_child);
	}

	p_parent_iterator = 
		unordered_map_iterator_alloc(p_graph_vertex->p_parents);

	// Disconnect from parents:
	while (unordered_map_iterator_has_next(p_parent_iterator)) 
	{
		unordered_map_iterator_next(p_parent_iterator,
									&p_parent,
									&p_weight);

		removeEdge(p_parent, p_graph_vertex);
	}

	// Free the children/parents maps:
	freeGraphVertex(p_graph_vertex);
}

int hasVertex(Graph* p_graph, size_t node_id)
{
	return unordered_map_contains_key(p_graph->p_nodes, 
								      node_id);
}

GraphVertex* getVertex(Graph* p_graph, size_t id) 
{
	void* p_value = unordered_map_get(p_graph->p_nodes, id);

	if (p_value) 
	{
		return (GraphVertex*) p_value;
	}

	return NULL;
}

void addEdge(Graph* p_graph,
			 size_t head_id,
			 size_t tail_id,
			 double weight)
{
	GraphVertex* p_head_vertex;
	GraphVertex* p_tail_vertex;

	p_head_vertex = addVertex(p_graph, head_id);
	p_tail_vertex = addVertex(p_graph, tail_id);

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
