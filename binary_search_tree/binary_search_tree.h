
#ifndef BINARY_SEARCH_TREE_HPP
# define BINARY_SEARCH_TREE_HPP

typedef struct	bst_node_s
{
	int					data;
	struct bst_node_s*	left_node;
	struct bst_node_s*	right_node;
}				bst_node_t;

#endif
