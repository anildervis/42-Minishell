/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:56:06 by aderviso          #+#    #+#             */
/*   Updated: 2023/04/02 11:46:37 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	iswhitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	char	*string;
	long	number;
	int		minus;
	int		i;

	string = (char *)str;
	number = 0;
	minus = 1;
	i = 0;
	while (iswhitespace(string[i]))
		i++;
	if (string[i] == '-')
		minus *= -1;
	if (string[i] == '+' || string[i] == '-')
		i++;
	while (string[i] >= '0' && string[i] <= '9')
	{
		number *= 10;
		number += string[i] - '0';
		i++;
	}
	return ((int)number * minus);
}
