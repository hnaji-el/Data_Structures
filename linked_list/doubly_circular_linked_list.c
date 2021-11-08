
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct	s_node
{
	int				data;
	struct s_node	*next;
	struct s_node	*prev;
}				t_node;

void	insert_at_beg(int data, t_node **head);

void	delete_at_beg(t_node **head);

t_node	*get_new_node(int data);
void	print_list(t_node *head);

t_node	*get_new_node(int data)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->data = data;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	insert_at_beg(int data, t_node **head)
{
	t_node	*node;

	node = get_new_node(data);
	if (*head == NULL)
	{
		node->next = node;
		node->prev = node;
		*head = node;
		return ;
	}
	node->next = *head;
	node->prev = (*head)->prev;
	(*head)->prev->next = node;
	(*head)->prev = node;
	*head = node;
}

void	delete_at_beg(t_node **head)
{
	t_node	*temp;

	if (*head == NULL)
		return ;
	if (*head == (*head)->next)
	{
		free(*head);
		*head = NULL;
		return ;
	}
	temp = *head;
	(*head)->prev->next = (*head)->next;
	(*head)->next->prev = (*head)->prev;
	*head = (*head)->next;
	free(temp);
}

void	print_list(t_node *head)
{
	t_node	*tail;

	if (head == NULL)
	{
		printf("the list is empty ...\n");
		return ;
	}
	tail = head->prev;
	while (head != tail)
	{
		printf("%d\n", head->data);
		head = head->next;
	}
	printf("%d\n", head->data);
}

int	main(void)
{
	t_node	*head;

	head = (void *)0;
	insert_at_beg(4, &head);
	insert_at_beg(3, &head);
	insert_at_beg(2, &head);
	insert_at_beg(1, &head);
	delete_at_beg(&head);
	delete_at_beg(&head);
	delete_at_beg(&head);
	delete_at_beg(&head);
	delete_at_beg(&head);
	delete_at_beg(&head);
	print_list(head);
	return (0);
}
