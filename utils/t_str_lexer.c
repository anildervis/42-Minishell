/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_str_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:15:56 by aderviso          #+#    #+#             */
/*   Updated: 2023/05/27 16:15:56 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	token_str_lexer(char *input)
{
	int	i;
	int	pair_check;

	i = 0;
	while (*(input + i) && is_metacharacter(*(input + i))
		&& ft_strnsearch((input + i), " \t\n", 1))
	{
		if (*(input + i) == *DOUBLE_QUOTE || *(input + i) == *SINGLE_QUOTE)
		{
			pair_check = find_pair(input + i, *(input + i)) + 1;
			if (pair_check == 0)
				i += ft_strlen(input + i);
			else
				i += pair_check;
		}
		else
			i++;
	}
	return (i);
}
