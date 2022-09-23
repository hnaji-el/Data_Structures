
#include "avl_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

avl_node_t*	get_new_node(int data)
{
	avl_node_t*	node;

	node = (avl_node_t*)malloc(sizeof(avl_node_t));
	if (node == NULL)
		return (NULL);
	node->data = data;
	node->left_node = NULL;
	node->right_node = NULL;
	node->height = 0;
	return (node);
}

int	get_height(avl_node_t* node)
{
	if (node == NULL)
    	return (-1);
	return (node->height);
}

int	max(int a, int b)
{
	return (a >= b ? a : b);
}

int	height_of_node(avl_node_t* node)
{
	int	const	left_height = get_height(node->left_node);
	int const	right_height = get_height(node->right_node);

	return (max(left_height, right_height) + 1);
}

int get_balance_factor(avl_node_t* node)
{
	int	const	left_height = get_height(node->left_node);
	int	const	right_height = get_height(node->right_node);

	return (left_height - right_height);
}

avl_node_t*	ll_rotation(avl_node_t* root)
{
	avl_node_t* lptr = root->left_node;

	root->left_node = lptr->right_node;
	lptr->right_node = root;

	// update height of (root, lptr)
	root->height = height_of_node(root);
	lptr->height = height_of_node(lptr);
	
	return (lptr);
}

avl_node_t*	rr_rotation(avl_node_t* root)
{
	avl_node_t* rptr = root->right_node;

	root->right_node = rptr->left_node;
	rptr->left_node = root;

	// update height of (root, rptr)
	root->height = height_of_node(root);
	rptr->height = height_of_node(rptr);
	
	return (rptr);
}

avl_node_t*	lr_rotation(avl_node_t* root)
{
	avl_node_t*	lptr = root->left_node;
	avl_node_t*	lrptr = lptr->right_node;

	root->left_node = lrptr->right_node;
	lptr->right_node = lrptr->left_node;
	lrptr->right_node = root;
	lrptr->left_node = lptr;

	// update height of (root, lptr, lrptr)
	root->height = height_of_node(root);
	lptr->height = height_of_node(lptr);
	lrptr->height = height_of_node(lrptr);

	return (lrptr);
}

avl_node_t*	rl_rotation(avl_node_t* root)
{
	avl_node_t*	rptr = root->right_node;
	avl_node_t*	rlptr = rptr->left_node;

	root->right_node = rlptr->left_node;
	rptr->left_node = rlptr->right_node;
	rlptr->left_node = root;
	rlptr->right_node = rptr;

	// update height of (root, rptr, rlptr)
	root->height = height_of_node(root);
	rptr->height = height_of_node(rptr);
	rlptr->height = height_of_node(rlptr);

	return (rlptr);
}

avl_node_t*	insert(int data, avl_node_t* root)
{
	int	balance_factor;

	if (root == NULL)
	{
		root = get_new_node(data);
		return (root);
	}
	else if (data < root->data)
		root->left_node = insert(data, root->left_node);
	else if (data > root->data)
		root->right_node = insert(data, root->right_node);

	// update height && balance_factor
	root->height = height_of_node(root);
	balance_factor = get_balance_factor(root);

	// check if balance or impalance then balance it if impalance.
	if (balance_factor == 2 && get_balance_factor(root->left_node) == 1)
		root = ll_rotation(root);
	else if (balance_factor == 2 && get_balance_factor(root->left_node) == -1)
		root = lr_rotation(root);
	else if (balance_factor == -2 && get_balance_factor(root->right_node) == 1)
		root = rl_rotation(root);
	else if (balance_factor == -2 && get_balance_factor(root->right_node) == -1)
		root = rr_rotation(root);

	return (root);
}

avl_node_t*	delete(int data, avl_node_t* root)
{
	int	balance_factor;

	if (root == NULL)
		return (NULL);
	else if (data > root->data)
		root->right_node = delete(data, root->right_node);
	else if (data < root->data)
		root->left_node = delete(data, root->left_node);
	// case#1: leaf node
	else if (root->left_node == NULL && root->right_node == NULL)
	{
		free(root);
		return (NULL);
	}
	// case#2: node with 1 Children
	else if (root->left_node == NULL)
	{
		avl_node_t*	rptr = root->right_node;
		free(root);
		root = rptr;
	}
	else if (root->right_node == NULL)
	{
		avl_node_t*	lptr = root->left_node;
		free(root);
		root = lptr;
	}
	// case#2: node with 2 Children
	else if (root->left_node != NULL && root->right_node != NULL)
	{
		avl_node_t*	temp = successor(root->right_node);
		root->data = temp->data;
		root->right_node = delete(temp->data, root->right_node);
	}

	// update height && balance_factor
	root->height = height_of_node(root);
	balance_factor = get_balance_factor(root);

	// check if balance or impalance then balance it if impalance.
	if (balance_factor == 2 && get_balance_factor(root->left_node) >= 0)
		root = ll_rotation(root);
	else if (balance_factor == 2 && get_balance_factor(root->left_node) == -1)
		root = lr_rotation(root);
	else if (balance_factor == -2 && get_balance_factor(root->right_node) <= 0)
		root = rr_rotation(root);
	else if (balance_factor == -2 && get_balance_factor(root->right_node) == 1)
		root = rl_rotation(root);

	return (root);
}

avl_node_t*	search(int data, avl_node_t* root)
{
	if (root == NULL || data == root->data)
		return (root);
	else if (data < root->data)
		return (search(data, root->left_node));
	else if (data > root->data)
		return (search(data, root->right_node));
	return (root);
}

avl_node_t*	successor(avl_node_t* root)
{
	while (root != NULL && root->left_node != NULL)
		root = root->left_node;
	return (root);
}

avl_node_t*	predecessor(avl_node_t* root)
{
	while (root != NULL && root->right_node != NULL)
		root = root->right_node;
	return (root);
}

void	preorder_traversal(avl_node_t* root)
{
	if (root == NULL)
		return ;
	printf("%d ", root->data);
	preorder_traversal(root->left_node);
	preorder_traversal(root->right_node);
}

void	inorder_traversal(avl_node_t* root)
{
	if (root == NULL)
		return ;
	inorder_traversal(root->left_node);
	printf("%d ", root->data);
	inorder_traversal(root->right_node);
}

void	postorder_traversal(avl_node_t* root)
{
	if (root == NULL)
		return ;
	postorder_traversal(root->left_node);
	postorder_traversal(root->right_node);
	printf("%d ", root->data);
}

int	main(void)
{
	avl_node_t*	root = NULL;

	root = insert(10, root);
	root = insert(20, root);
	root = insert(30, root);
	root = insert(25, root);
	root = insert(28, root);
	root = insert(27, root);
	root = insert(5, root);

	preorder_traversal(root);
	printf("\n");

	root = delete(30, root);
	preorder_traversal(root); printf("\n");
	root = delete(28, root);
	preorder_traversal(root); printf("\n");
	root = delete(27, root);
	preorder_traversal(root); printf("\n");
	root = delete(10, root);
	preorder_traversal(root); printf("\n");
	root = delete(5, root);
	preorder_traversal(root); printf("\n");
	root = delete(20, root);
	preorder_traversal(root); printf("\n");
	root = delete(25, root);
	preorder_traversal(root); printf("\n");

	return (0);
}
