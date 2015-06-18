/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/01 15:53:14 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/13 15:34:45 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_nbrlen_base(long long int n, int base)
{
	int	r;

	r = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		r++;
		n = n / base;
	}
	return (r);
}

int		ft_nbrlen(long long int n)
{
	int	r;

	r = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		r++;
		n = n / 10;
	}
	return (r);
}
