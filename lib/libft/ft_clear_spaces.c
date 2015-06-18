/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/07 11:37:07 by rpereira          #+#    #+#             */
/*   Updated: 2014/12/29 18:49:47 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_clear_spaces(char *line)
{
	char	*ret;
	int		len;
	int		j;

	if (line == NULL)
		return (NULL);
	j = 0;
	len = ft_strlen(line) - ft_ccount(line, ' ') + 1;
	ret = (char*)malloc(sizeof(char) * len);
	while (*line)
	{
		if (*line != ' ')
		{
			ret[j] = *line;
			j++;
		}
		line++;
	}
	ret[j] = '\0';
	return (ret);
}
