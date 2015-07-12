/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <rpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 10:03:09 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/07 16:56:33 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	list_new(void)
{
	t_list	list;

	list.head = (t_list_node*)malloc(sizeof(t_list_node));
	list.head->next = list.head;
	list.head->previous = list.head;
	list.size = 0;
	return (list);
}

void	list_remove_node(t_list *lst, t_list_node *node, t_function free_funct)
{
	if (node->previous)
	{
		node->previous->next = node->next;
	}
	if (node->next)
	{
		node->next->previous = node->previous;
	}

	node->next = NULL;
	node->previous = NULL;

	free_funct(node + 1);
	free(node);
	lst->size--;
}

/** remove if the comparison return elements are equals (works like strcmp) */
int 	list_remove(t_list *lst, t_function free_funct, t_cmp_func cmpf, void *cmpd)
{
	t_list_node	*node;

	node = lst->head->next;
	while (node != lst->head)
	{
		if (cmpf(node + 1, cmpd) == 0)
		{
			list_remove_node(lst, node, free_funct);
			return (1);
		}
		node = node->next;
	}
	return (0);
}

/** the content of size content_size is stored just after the node, so only 1 malloc is used */
void 	*list_add(t_list *lst, void const *content, size_t content_size)
{
	t_list_node	*node;
	t_list_node	*tmp;

	node = (t_list_node*)malloc(sizeof(t_list_node) + content_size);
	if (node == NULL)
	{
		return (NULL);
	}
	memcpy(node + 1, content, content_size);

	tmp = lst->head->next;

	lst->head->next = node;
	tmp->previous = node;

	node->previous = lst->head;
	node->next = tmp;

	lst->size++;

	return (node + 1);
}

void 	*list_push(t_list *lst, void const *content, size_t content_size)
{
	t_list_node	*node;
	t_list_node	*tmp;

	node = (t_list_node*)malloc(sizeof(t_list_node) + content_size);
	if (node == NULL)
	{
		return (NULL);
	}
	memcpy(node + 1, content, content_size);
	
	tmp = lst->head->previous;

	lst->head->previous = node;
	tmp->next = node;

	node->previous = tmp;
	node->next = lst->head;

	lst->size++;

	return (node + 1);
}

void 	*list_get(t_list *lst, t_cmp_func cmpf, void *cmpd)
{
	t_list_node	*node;

	node = lst->head->next;
	while (node != lst->head)
	{
		if (cmpf(node + 1, cmpd) == 0)
		{
			return (node + 1);
		}
		node = node->next;
	}
	return (NULL);
}

void	list_delete(t_list *lst, void (*delete_content)(void *content))
{
	t_list_node	*node;
	t_list_node	*next;

	node = lst->head->next;
	while (node != lst->head)
	{
		next = node->next;
		delete_content(node + 1);
		free(node);
		node = next;
	}
	free(lst->head);
	lst->head = NULL;
	lst->size = 0;
}
