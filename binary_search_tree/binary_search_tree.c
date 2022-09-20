
#include "binary_search_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

bst_node_t*	get_new_node(int data)
{
	bst_node_t*	node;

	node = (bst_node_t*)malloc(sizeof(bst_node_t));
	if (node == NULL)
		return (NULL);
	node->data = data;
	node->left_node = NULL;
	node->right_node = NULL;
	return (node);
}

void	insert(int data, bst_node_t** root)
{
	if (*root == NULL)
		*root = get_new_node(data);
	else if (data < (*root)->data)
		insert(data, &((*root)->left_node));
	else if (data > (*root)->data)
		insert(data, &((*root)->right_node));
}

bst_node_t*	search(int data, bst_node_t* root)
{
	if (root == NULL || data == root->data)
		return (root);
	else if (data < root->data)
		return (search(data, root->left_node));
	else if (data > root->data)
		return (search(data, root->right_node));
	return (root);
}

bst_node_t*	successor(bst_node_t* root)
{
	while (root != NULL && root->left_node != NULL)
		root = root->left_node;
	return (root);
}

bst_node_t*	predecessor(bst_node_t* root)
{
	while (root != NULL && root->right_node != NULL)
		root = root->right_node;
	return (root);
}

void	delete(int data, bst_node_t** root)
{
	if (*root == NULL)
		return ;
	else if (data > (*root)->data)
		delete(data, &((*root)->right_node));
	else if (data < (*root)->data)
		delete(data, &((*root)->left_node));
	// case#1: leaf nodes
	else if ((*root)->left_node == NULL && (*root)->right_node == NULL)
	{
		free(*root);
		*root = NULL;
	}
	// case#2: nodes with 1 Children
	else if ((*root)->left_node == NULL)
	{
		bst_node_t*	temp = *root;
		*root = (*root)->right_node;
		free(temp);
	}
	else if ((*root)->right_node == NULL)
	{
		bst_node_t*	temp = *root;
		*root = (*root)->left_node;
		free(temp);
	}
	// case#2: nodes with 2 Children
	else if ((*root)->left_node != NULL && (*root)->right_node != NULL)
	{
		bst_node_t*	temp = successor((*root)->right_node);
		(*root)->data = temp->data;
		delete(temp->data, &((*root)->right_node));
	}
}

int	max(int a, int b)
{
	return (a >= b ? a : b);
}

// Time complexity: O(n) one recursive call corresponding to each node in tree

int	height_of_bst(bst_node_t* root)
{
	if (root == NULL)
		return (-1);
	int	height_of_lsubtree = height_of_bst(root->left_node);
	int	height_of_rsubtree = height_of_bst(root->right_node);
	return (max(height_of_lsubtree, height_of_rsubtree) + 1);
}

// Time complexity: O(n) one recursive call corresponding to each node in tree

void	preorder_traversal(bst_node_t* root)
{
	if (root == NULL)
		return ;
	printf("%d ", root->data);
	preorder_traversal(root->left_node);
	preorder_traversal(root->right_node);
}

void	inorder_traversal(bst_node_t* root)
{
	if (root == NULL)
		return ;
	inorder_traversal(root->left_node);
	printf("%d ", root->data);
	inorder_traversal(root->right_node);
}

void	postorder_traversal(bst_node_t* root)
{
	if (root == NULL)
		return ;
	postorder_traversal(root->left_node);
	postorder_traversal(root->right_node);
	printf("%d ", root->data);
}

int	main(void)
{
	bst_node_t*	root;
	bst_node_t*	temp;

	root = NULL; // empty BST
	insert(20, &root);
	insert(10, &root);
	insert(30, &root);
	insert(5, &root);
	insert(15, &root);
	insert(25, &root);
	insert(35, &root);

	inorder_traversal(root);

	return (0);
}
