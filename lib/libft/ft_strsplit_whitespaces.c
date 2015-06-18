/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_spaces.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 15:48:42 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/02 15:48:50 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	whitespace_tab_size(const char *s)
{
	int	size;

	size = 0;
	while (*s)
	{
		while (*s && (*s == ' ' || *s == '\t'))
			s++;
		if (!*s)
			return (size);
		size = size + 1;
		while (*s && *s != ' ' && *s != '\t')
			s++;
	}
	return (size);
}

static int	whitespace_elem_size(const char *s)
{
	int	size;

	size = 0;
	while (*s && *s != ' ' && *s != '\t')
	{
		s++;
		size++;
	}
	return (size);
}

char		**ft_strsplit_whitespaces(char const *s)
{
	char	**tab;
	int		elem_size;
	int		tab_len;
	int		i;

	if (!s)
		return (NULL);
	tab_len = whitespace_tab_size(s);
	tab = (char**)malloc(sizeof(char*) * (tab_len + 2));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < tab_len)
	{
		while (*s && (*s == ' ' || *s == '\t'))
			s++;
		elem_size = whitespace_elem_size(s);
		tab[i] = malloc(elem_size + 1);
		memcpy(tab[i], s, elem_size);
		tab[i][elem_size] = 0;
		s = s + elem_size + 1;
		i++;
	}
	tab[tab_len] = NULL;
	return (tab);
}
