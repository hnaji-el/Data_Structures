
#ifndef AVL_TREE_H
# define AVL_TREE_H

typedef struct	avl_node_s
{
	int		data;
	struct avl_node_s*	left_node;
	struct avl_node_s*	right_node;
	int		height;
	int		balance_factor;
}				avl_node_t;

avl_node_t*	get_new_node(int data);
int	get_height(avl_node_t* node);
int	get_height_of_node(avl_node_t* node);
int get_balance_factor(avl_node_t* node);
int	max(int a, int b);
avl_node_t*	ll_rotation(avl_node_t* root);
avl_node_t*	rr_rotation(avl_node_t* root);
avl_node_t*	lr_rotation(avl_node_t* root);
avl_node_t*	rl_rotation(avl_node_t* root);
avl_node_t*	insert(int data, avl_node_t* root);
void	inorder_traversal(avl_node_t* root);
void	preorder_traversal(avl_node_t* root);
avl_node_t*	successor(avl_node_t* root);

#endif
