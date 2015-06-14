/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 16:29:40 by rpereira          #+#    #+#             */
/*   Updated: 2015/01/19 13:55:18 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	split_tab_size(const char *s, char c)
{
	int	size;

	size = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			return (size);
		size = size + 1;
		while (*s && *s != c)
			s++;
	}
	return (size);
}

static int	split_elem_size(const char *s, char c)
{
	int	size;

	size = 0;
	while (*s && *s != c)
	{
		s++;
		size++;
	}
	return (size);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		elem_size;
	int		tab_len;
	int		i;

	if (s == NULL)
		return (NULL);
	tab_len = split_tab_size(s, c);
	tab = (char**)malloc(sizeof(char*) * (tab_len + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (i < tab_len)
	{
		while (*s && *s == c)
			s++;
		elem_size = split_elem_size(s, c);
		tab[i] = memcpy(malloc(elem_size + 1), s, elem_size);
		tab[i][elem_size] = 0;
		s += elem_size + 1;
		i++;
	}
	tab[tab_len] = NULL;
	return (tab);
}
