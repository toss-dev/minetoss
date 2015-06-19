/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <rpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 14:01:04 by rpereira          #+#    #+#             */
/*   Updated: 2014/12/30 12:37:53 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char			*ret;
	unsigned int	len;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	len = strlen(s) - 1;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	ret = (char*) malloc(len - i + 1);
	if (ret == NULL)
		return (NULL);
	while (len > 0 && (s[len] == '\n' || s[len] == ' ' || s[len] == '\t'))
		len--;
	len = len - i + 1;
	ret[len] = 0;
	return (memcpy(ret, s + i, len));
}
