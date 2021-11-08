
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct	s_node
{
	int				data;
	struct s_node	*link;
}				t_node;

void	insert_at_beg(int data, t_node **head);
void	insert_at_end(int data, t_node **head);
void	insert_at_n(int data, int n, t_node **head);

void	delete_at_beg(t_node **head);
void	delete_at_end(t_node **head);
void	delete_at_n(int n, t_node **head);

t_node	*create_node(int data);
t_node	*traverse_ll(t_node *head);
int		strlen_list(t_node *head);
void	print_ll(t_node *head);

t_node	*create_node(int data)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->data = data;
	node->link = NULL;
	return (node);
}

void	insert_at_beg(int data, t_node **head)
{
	t_node	*node;

	node = create_node(data);
	node->link = *head;
	*head = node;
}

void	insert_at_end(int data, t_node **head)
{
	t_node	*node;
	t_node	*temp1;

	node = create_node(data);
	if (*head == NULL)
		*head = node;
	else
	{
		temp1 = traverse_ll(*head);
		temp1->link = node;
	}
}

void	insert_at_n(int data, int n, t_node **head)
{
	t_node	*node;
	t_node	*temp;
	int		length;
	int		i;

	i = 0;
	temp = *head;
	length = strlen_list(*head);
	if (n < 1 || n > length + 1)
	{
		printf("Error ....\n");
		return ;
	}
	if (n == 1)
	{
		insert_at_beg(data, head);
		return ;
	}
	node = create_node(data);
	while (++i < n - 1)
		temp = temp->link;
	node->link = temp->link;
	temp->link = node;
}

void	delete_at_beg(t_node **head)
{
	t_node	*temp;

	temp = *head;
	if (*head == NULL)
		return ;
	*head = temp->link;
	free(temp);
}

void	delete_at_end(t_node **head)
{
	t_node	*temp;

	temp = *head;
	if (*head == NULL)
		return ;
	if ((*head)->link == NULL)
	{
		free(*head);
		*head = NULL;
		return ;
	}
	while ((temp->link)->link != NULL)
		temp = temp->link;
	free(temp->link);
	temp->link = NULL;
}

void	delete_at_n(int n, t_node **head)
{
	t_node	*temp1;
	t_node	*temp2;
	int		length;
	int		i;

	i = 0;
	temp1 = *head;
	length = strlen_list(*head);
	if (n < 1 || n > length)
		return ;
	if (n == 1)
	{
		delete_at_beg(head);
		return ;
	}
	while (++i < n - 1)
		temp1 = temp1->link;
	temp2 = temp1->link;
	temp1->link = temp2->link;
	free(temp2);
}

int		strlen_list(t_node *head)
{
	int		length;

	length = 0;
	if (head == NULL)
		return (length);
	while (head->link != NULL)
	{
		length++;
		head = head->link;
	}
	return (length + 1);
}

t_node *traverse_ll(t_node *head)
{
	while (head->link != NULL)
	{
		head = head->link;
	}
	return (head);
}

void	print_ll(t_node *head)
{
	if (head == NULL)
	{
		printf("empty list ...\n");
		return ;
	}
	while (head != NULL)
	{
		printf("%d\n", head->data);
		head = head->link;
	}
}

int	main(void)
{
	t_node	*head;

	head = (void *)0;
	insert_at_beg(3, &head);
	insert_at_beg(2, &head);
	insert_at_beg(1, &head);
	delete_at_n(3, &head);
	delete_at_n(2, &head);
	delete_at_n(2, &head);
	print_ll(head);
	return (0);
}
