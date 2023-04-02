/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:35:27 by aderviso          #+#    #+#             */
/*   Updated: 2022/10/23 13:09:12 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_number_length(long int n)
{
	long int	i;
	long int	temp_number;

	i = 0;
	if (n == 0)
		return (1);
	temp_number = n;
	if (temp_number < 0)
	{
		temp_number *= -1;
		i++;
	}
	while (temp_number >= 1)
	{
		temp_number /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*number;
	int			i;
	long int	rt;

	rt = (long int)n;
	number = malloc(sizeof(char) * (ft_number_length(n) + 1));
	i = 0;
	if (!number)
		return (0);
	number[ft_number_length(n)] = 0;
	if (rt == 0)
		number[0] = '0';
	if (rt < 0)
	{
		number[i] = '-';
		rt *= -1;
	}
	while (rt >= 1)
	{
		number[ft_number_length(n) - 1 - i] = (rt % 10) + '0';
		rt /= 10;
		i++;
	}
	return (number);
}
