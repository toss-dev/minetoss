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
	if ((elem.content = malloc(data_size)) == NULL)
	{
		free(elem.key);
		return (NULL);
	}
	elem.content_size = data_size;
	memcpy(elem.content, data, data_size);
	list_add(tab.elems + hash, &elem, sizeof(t_htab_elem));
	return (elem.content);
}

void	*htab_get(t_htab tab, char *key)
{
	t_list		*lst;
	t_node		*tmp;
	t_htab_elem	*elem;
	size_t		hash;

	hash = htab_hash(key, tab.size);
	if ((lst = tab.elems + hash) == NULL)
		return (NULL);
	tmp = lst->begin;
	while (tmp)
	{
		elem = (t_htab_elem*)tmp->content;
		if (strcmp(elem->key, key) == 0)
			return (elem->content);
		tmp = tmp->next;
	}
	return (NULL);
}

static void	htab_free_elem(t_htab_elem *elem)
{
	free(elem->key);
	free(elem->content);
	free(elem);
}

static int	htab_list_remove_cmp(t_htab_elem *elem, char const *key)
{
	return (strcmp(elem->key, key));
}

bool		htab_remove(t_htab tab, char *key)
{
	t_list	*lst;
	size_t	hash;

	hash = htab_hash(key, tab.size);
	if ((lst = tab.elems + hash) == NULL)
		return (false);
	list_remove_if(lst, htab_free_elem, (t_cmp_func)htab_list_remove_cmp, key);
	return (true);
}

t_htab		htab_new(size_t size)
{
	t_htab	tab;

	tab.size = size;
	tab.elems = (t_list*)malloc(sizeof(t_list) * size);
	memset(tab.elems, 0, sizeof(t_list) * size);
	return (tab);
}

static void	htab_list_delete(t_list *lst, void (*delete_node)(void *content))
{
	t_node		*tmp;
	t_node		*next;
	t_htab_elem	*elem;

	if (delete_node == NULL)
		delete_node = free;
	tmp = lst->begin;
	while (tmp)
	{
		next = tmp->next;
		elem = (t_htab_elem*)tmp->content;
		delete_node(elem->content);
		free(elem->key);
		free(elem);
		free(tmp);
		tmp = next;
	}
}

void		htab_delete(t_htab *tab, void (*delete_node)(void *content))
{
	size_t	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (i < tab->size)
	{
		if (tab->elems + i != NULL)
		{
			htab_list_delete(tab->elems + i, delete_node);
		}
		i++;
	}
	free(tab->elems);
}
