/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 13:55:27 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/09 10:25:15 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strsplit_free(char **tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int		ft_strsplit_size(char **tab)
{
	int	i;

	if (tab == NULL)
		return (0);
	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

int		ft_strsplit_contains(char **tab, char *sequence)
{
	void	*ptr;
	int		i;

	if (tab == NULL)
		return (-1);
	i = 0;
	while (tab[i] != NULL)
	{
		ptr = strstr(tab[i], sequence);
		if (ptr != NULL)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_swip_strsplit(char **tab, int from, int nb)
{
	void	*ptr;
	int		left;
	int		len;

	if (tab == NULL)
		return ;
	len = ft_strsplit_size(tab);
	if (from >= len)
		return ;
	left = 0;
	while (left < nb && from - left - 1 >= 0)
	{
		ptr = tab[from - left - 1];
		tab[from - left - 1] = tab[from - left];
		tab[from - left] = ptr;
		left++;
	}
}
