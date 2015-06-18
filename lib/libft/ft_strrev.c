/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <rpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 10:52:05 by rpereira          #+#    #+#             */
/*   Updated: 2014/12/29 17:46:06 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	char	c;
	int		size;
	int		j;

	if (str == NULL)
		return (str);
	size = ft_strlen(str);
	j = 0;
	while (j < size / 2)
	{
		c = str[j];
		str[j] = str[size - 1 - j];
		str[size - 1 - j] = c;
		j++;
	}
	return (str);
}
