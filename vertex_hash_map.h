#ifndef COM_GITHUB_CODERODDE_PERL_GRAPH_HASH_MAP_H
#define COM_GITHUB_CODERODDE_PERL_GRAPH_HASH_MAP_H

#include <stdlib.h>

typedef struct VertexHashMapNode {
	size_t node_id;
	double weight;
	VertexHashMapNode* p_next_node;
} VertexHashMapNode;

typedef struct VertexHashMap {
	VertexHashMapNode** p_table;
	size_t size;
	size_t capacity;
} VertexHashMap;

void map(VertexHashMap* p_vertex_hash_map, 
		 size_t node_id,
		 double weight);

double get(VertexHashMap* p_vertex_hash_map,
		   size_t node_id);

void remove(VertexHashMap* p_vertex_hash_map,
			size_t node_id);

#endif // COM_GITHUB_CODERODDE_PERL_GRAPH_HASH_MAP_H