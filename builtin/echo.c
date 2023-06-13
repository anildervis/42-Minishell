/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:11:51 by binurtas          #+#    #+#             */
/*   Updated: 2023/06/12 14:57:06 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_char(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		write(1, &input[i], 1);
		i++;
	}
}

void	builtin_echo(char **input)
{
	int	i;
	int	j;

	i = 1;
	while (input[i] && !ft_strncmp(input[i], "-n", 2))
	{
		j = 1;
		while (input[i][j] && input[i][j] == 'n')
			j++;
		if (input[i][j] != '\0')
			break ;
		i++;
	}
	while (input[i])
	{
		put_char(input[i]);
		if (input[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	ft_check_enter(input);
}

void	ft_check_enter(char **input)
{
	int	i;

	i = 1;
	if (input[1] && !ft_strncmp(input[1], "-n", 2))
		while (input[1][i] && input[1][i] == 'n')
			i++;
	if (input[1][i] != '\0' || i == 1)
		write(STDOUT_FILENO, "\n", 1);
}
