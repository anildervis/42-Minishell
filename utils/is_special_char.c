/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_special_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:57:00 by binurtas          #+#    #+#             */
/*   Updated: 2023/06/15 17:38:31 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_special_finder(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != '=')
	{
		if (is_special_char(input[i]))
			return (1);
		i++;
	}
	return (0);
}

int	is_special_char(char c)
{
	if ((c >= 42 && c <= 47) || (c <= 64 && c >= 63)
		|| (c == '[') || (c == ']') || (c == '^') || (c == '{') || (c == '}')
		|| (c == '~') || (c == '#') || (c == '%'))
		return (1);
	return (0);
}
