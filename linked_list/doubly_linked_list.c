
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct	s_node
{
	int				data;
	struct s_node	*next;
	struct s_node 	*prev;
}				t_node;

void	insert_at_beg(int data, t_node **head);
void	print_list(t_node *head);
void	print_reverse_list(t_node *head);
t_node	*create_node(int data);
void	traverse_dll(t_node **head);

t_node	*create_node(int data)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->data = data;
	node->next = (void *)0;
	node->prev = (void *)0;
	return (node);
}

void	insert_at_beg(int data, t_node **head)
{
	t_node	*node;

	node = create_node(data);
	if (*head == NULL)
	{
		*head = node;
		return ;
	}
	(*head)->prev = node;
	node->next = *head;
	*head = node;
}

void	traverse_dll(t_node **head)
{
	if (*head == NULL)
		return ;
	while ((*head)->next != NULL)
		*head = (*head)->next;
}

void	print_list(t_node *head)
{
	while (head != NULL)
	{
		printf("%d\n", head->data);
		head = head->next;
	}
}

void	print_reverse_list(t_node *head)
{
	traverse_dll(&head);
	while (head != NULL)
	{
		printf("%d\n", head->data);
		head = head->prev;
	}
}

int	main(void)
{
	t_node *head;

	head = (void *)0;
	insert_at_beg(4, &head);
	print_list(head);
	printf("----------------------\n");
	print_reverse_list(head);
	printf("-\n");
	insert_at_beg(3, &head);
	print_list(head);
	printf("----------------------\n");
	print_reverse_list(head);
	printf("-\n");
	insert_at_beg(2, &head);
	print_list(head);
	printf("----------------------\n");
	print_reverse_list(head);
	printf("-\n");
	insert_at_beg(1, &head);
	print_list(head);
	printf("----------------------\n");
	print_reverse_list(head);
	printf("-\n");
	return (0);
}
