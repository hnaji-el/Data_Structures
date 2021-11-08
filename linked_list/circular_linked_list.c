
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct	s_node
{
	int				data;
	struct s_node	*next;
}				t_node;

void	insert_at_beg(int data, t_node **tail);
void	insert_at_end(int data, t_node **tail);
void	insert_at_n(int data, int n, t_node **tail);

void	delete_at_beg(t_node **tail);
void	delete_at_end(t_node **tail);
void	delete_at_n(int n, t_node **tail);

t_node	*get_new_node(int data);
void	print_list(t_node *tail);
int		strlen_list(t_node *tail);

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

void	insert_at_end(int data, t_node **tail)
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
	*tail = node;
}

void	insert_at_n(int data, int n, t_node **tail)
{
	t_node	*node;
	t_node	*temp;
	int		length;
	int		i;

	i = 0;
	length = strlen_list(*tail);
	if (n < 1 || n > length + 1)
	{
		printf("Error ...\n");
		return ;
	}
	if (n == 1)
		insert_at_beg(data, tail);
	else if (n == length + 1)
		insert_at_end(data, tail);
	else
	{
		node = get_new_node(data);
		temp = (*tail)->next;
		while (++i < n - 1)
			temp = temp->next;
		node->next = temp->next;
		temp->next = node;
	}
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

void	delete_at_end(t_node **tail)
{
	t_node	*temp1;

	if (*tail == NULL)
		return ;
	temp1 = (*tail)->next;
	if (temp1 == *tail)
	{
		*tail = NULL;
		free(temp1);
		return ;
	}
	while (temp1->next != *tail)
		temp1 = temp1->next;
	temp1->next = (*tail)->next;
	free(*tail);
	*tail = temp1;
}

void	delete_at_n(int n, t_node **tail)
{
	t_node	*temp1;
	t_node	*temp2;
	int		length;
	int		i;

	i = 0;
	length = strlen_list(*tail);
	if (n < 1 || n > length)
	{
		printf("Error: n not valid position in CLL ...\n");
		return ;
	}
	if (n == 1)
	{
		delete_at_beg(tail);
		return ;
	}
	temp1 = (*tail)->next;
	while (++i < n - 1)
		temp1 = temp1->next;
	temp2 = temp1->next;
	temp1->next = temp2->next;
	if (temp2 == *tail)
		*tail = temp1;
	free(temp2);
}

int		strlen_list(t_node *tail)
{
	t_node	*head;
	int		length;

	length = 0;
	if (tail == NULL)
		return (length);
	head = tail->next;
	while (head != tail)
	{
		length++;
		head = head->next;
	}
	return (length + 1);
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
	t_node	*tail;

	tail = (void *)0;
	insert_at_end(4 ,&tail);
	insert_at_end(3 ,&tail);
	insert_at_end(2 ,&tail);
	print_list(tail);
	return (0);
}
