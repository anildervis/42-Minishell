/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:11:51 by binurtas          #+#    #+#             */
/*   Updated: 2023/05/20 14:11:52 by binurtas         ###   ########.fr       */
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

	i = 1;
	while (!ft_strcmp(input[i], "-n"))
		i++;
	while (input[i])
	{
		put_char(input[i]);
		if (input[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (ft_strcmp(input[1], "-n"))
		write(STDOUT_FILENO, "\n", 1);
	if (g_ms.parent_pid != getpid())
		exit(0);
}
