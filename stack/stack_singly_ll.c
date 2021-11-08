
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct	s_node
{
	int				data;
	struct s_node	*link;
}				t_node;

typedef struct	s_stack
{
	t_node	*top;
	char	*name;
	int		length;
}				t_stack;

t_node	*create_node(int data);
t_stack	*create_empty_stack(char *name);
void	push(int data, t_stack *stack);
void	pop(t_stack *stack);

t_stack	*create_empty_stack(char *name)
{
	t_stack	*stack;

	stack = (t_stack *)malloc(sizeof(t_stack));
	stack->top = (void *)0;
	stack->name = name;
	stack->length = 0;
	return (stack);
}

t_node	*create_node(int data)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->data = data;
	node->link = NULL;
	return (node);
}

void	push(int data, t_stack *stack)
{
	t_node	*node;

	node = create_node(data);
	node->link = stack->top;
	stack->top = node;
}

void	pop(t_stack *stack)
{
	t_node	*temp;

	temp = stack->top;
	if (stack->top == NULL)
		return ;
	stack->top = temp->link;
	free(temp);
}

void	print(t_stack *stack)
{
	t_node	*temp;

	temp = stack->top;
	if (stack->top == NULL)
	{
		printf("the stack is empty ...\n");
		return ;
	}
	while (temp != NULL)
	{
		printf("%d\n", temp->data);
		temp = temp->link;
	}
}

int	main(void)
{
	t_stack		*stack;

	stack = create_empty_stack("a");
	push(3, stack);
	push(2, stack);
	push(1, stack);
	pop(stack);
	pop(stack);
	pop(stack);
	pop(stack);
	pop(stack);
	print(stack);
	return (0);
}
