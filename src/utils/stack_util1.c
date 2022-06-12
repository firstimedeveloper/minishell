#include "minishell.h"

void init_stack(t_stack *s)
{
	s->top = -1;
}

int	is_empty(t_stack *s)
{
	if (s->top == -1)
		return (0);
	return (-1);
}

int	is_full(t_stack *s)
{
	if (s->top == MAX-1)
		return (0);
	return (-1);
}

int	pop(t_stack *s)
{
	if (is_empty(s))
		return (-1);
	return (s->items[s->top--]);
}

int	push(t_stack *s, int value)
{
	if (is_full(s))
		return (-1);
	s->items[++(s->top)] = value;
	return (0);
}
