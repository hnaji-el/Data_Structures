
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct	s_node
{
	int				data;
	struct s_node	*next;
}				t_node;

typedef struct	

void	insert_at_beg(int data, t_node **tail);

void	delete_at_beg(t_node **tail);

t_node	*get_new_node(int data);
void	print_list(t_node *tail);

t_node	*get_new_node(int data)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->data = data;
	node->next = NULL;
	return (node);
}

void	insert_at_beg(int data, t_node **tail)
{
	t_node	*node;
	
	node = get_new_node(data);
	if (*tail == NULL)
	{
		node->next = node;
		*tail = node;
		return ;
	}
	node->next = (*tail)->next;
	(*tail)->next = node;
}

void	delete_at_beg(t_node **tail)
{
	t_node	*temp;

	if (*tail == NULL)
		return ;
	temp = (*tail)->next;
	(*tail)->next = temp->next;
	if (temp == *tail)
		*tail = (void *)0;
	free(temp);
}

void	print_list(t_node *tail)
{
	t_node	*head;
	
	if (tail == NULL)
	{
		printf("the list is empty ...\n");
		return ;
	}
	head = tail->next;
	while (head != tail)
	{
		printf("%d\n", head->data);
		head = head->next;
	}
	printf("%d\n", head->data);
}

int	main(void)
{
	t_node	*top;

	top = (void *)0;
	return (0);
}
