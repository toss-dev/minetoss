/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 10:50:23 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/13 04:48:28 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack stack_new(void)
{
	t_stack	stack;

	stack.head = NULL;
	stack.size = 0;
	return (stack);
}

/** return the content store in the node */
void 	*stack_get_node_content(t_stack_node *node)
{
	return (node + 1);
}

/** push the content at the top of the stack */
void	*stack_push(t_stack *stack, void *content, size_t size)
{
	t_stack_node	*node;

	node = (void*)malloc(sizeof(t_stack_node) + size);
	if (node == NULL)
	{
		return (NULL);
	}
	node->next = stack->head;
	memcpy(node + 1, content, size);
	stack->head = node;
	stack->size++;
	return (stack->head);
}

void 	stack_pop(t_stack *stack)
{
	t_stack_node	*node;

	if (stack->head)
	{
		node = stack->head->next;
		free(stack->head);
		stack->head = node;
		stack->size--;
	}
}

size_t	stack_size(t_stack *stack)
{
	return (stack->size);
}

void 	stack_delete(t_stack *stack)
{
	while (stack->head)
	{
		stack_pop(stack);
	}
}

void	*stack_head(t_stack *stack)
{
	if (stack->head)
	{
		return (stack->head + 1);
	}
	return (NULL);
}