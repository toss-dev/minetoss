/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   htab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 21:11:24 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/14 23:01:58 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		htab_hash(char *str, size_t size)
{
	size_t	hash;
	int		c;

	if (str == NULL)
		return (0);
	hash = 5381;
	while ((c = *str) != '\0')
	{
		hash = ((hash << 5) + hash) + c;
		str++;
	}
	return (hash % size);
}

/** return a pointer to the added data, or null if it failed */
void		*htab_insert(t_htab tab, char *key, void *data, size_t data_size)
{
	t_htab_elem	elem;
	size_t		hash;

	hash = htab_hash(key, tab.size);
	if ((elem.key = strdup(key)) == NULL)
		return (NULL);
	if ((elem.content = ft_memdup(data, data_size)) == NULL)
	{
		free(elem.key);
		return (NULL);
	}
	list_add(tab.elems + hash, &elem, sizeof(t_htab_elem));
	return (elem.content);
}

void	*htab_get(t_htab tab, char *key)
{
	t_list		*lst;
	t_node		*node;
	t_htab_elem	*elem;
	size_t		hash;

	hash = htab_hash(key, tab.size);
	lst = tab.elems + hash;
	node = lst->head->next;
	while (node != lst->head)
	{
		elem = (t_htab_elem*)node->content;
		if (strcmp(elem->key, key) == 0)
		{
			return (elem->content);
		}
		node = node->next;
	}
	return (NULL);
}

int			htab_remove_key(t_htab tab, char *key, t_function free_funct)
{
	t_list		*lst;
	t_node		*node;
	t_htab_elem	*elem;
	size_t		hash;

	hash = htab_hash(key, tab.size);
	lst = tab.elems + hash;
	node = lst->head->next;
	while (node != lst->head)
	{
		elem = (t_htab_elem*)node->content;
		if (strcmp(elem->key, key) == 0)
		{
			free(elem->key);
			free_funct(elem->content);
			list_remove_node(lst, node, free);
			return (1);
		}
		node = node->next;
	}
	return (0);
}

t_htab		htab_new(size_t size)
{
	t_htab			tab;
	unsigned int 	i;

	tab.size = size;
	tab.elems = (t_list*)malloc(sizeof(t_list) * size);
	for (i = 0 ; i < size ; i++)
	{
		tab.elems[i] = list_new();
	}
	return (tab);
}

void		htab_dump_memory(t_htab tab)
{
	unsigned int 	i;
	unsigned char	*memory;
	unsigned int 	size;
	unsigned		m;

	memory = (unsigned char*)tab.elems;
	size = tab.size * sizeof(t_list);
	m = sizeof(t_list) * 2;
	for (i = 0 ; i < size ; i++)
	{
		if (i % m == 0 && i != 0)
		{
			printf(" | \n");
		}
		if (i % sizeof(t_list) == 0)
		{
			printf(" | ");
		}
		printf("%.2x ", memory[i]);
	}
	printf(" | \n");
	fflush(stdout);
}

void		htab_delete(t_htab *tab, void (*delete_node)(void *))
{
	//TODO: free properly htab_elem with delete_node function

	(void)delete_node;
	size_t	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (i < tab->size)
	{
		list_delete(tab->elems + i, free);
		i++;
	}
	free(tab->elems);
	tab->elems = NULL;
}
