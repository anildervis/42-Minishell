/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:11:56 by binurtas          #+#    #+#             */
/*   Updated: 2023/06/15 18:43:29 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_get_arg_count(char **input)
{
	int	i;

	i = 0;
	while (input[i])
		i++;
	return (i);
}

int	ft_isnumber_with_sign(char *arg)
{
	while (*arg)
	{
		if ((*arg >= '0' && *arg <= '9') || *arg == '+' || *arg == '-')
			arg++;
		else
			return (0);
	}
	return (1);
}

void	builtin_exit(char **input)
{
	if (ft_get_arg_count(input) == 1)
	{
		printf("exit\n");
		free_tokens(g_ms.tokens);
		free_parsed_commands(g_ms.parsed_commands);
		exit(g_ms.error_no);
	}
	else
	{
		if (ft_isnumber_with_sign(input[1]))
		{
			if (ft_get_arg_count(input) > 2)
			{
				write(2, "exit\nminishel: exit: too many arguments\n", 41);
				g_ms.error_no = 1;
				return ;
			}
			printf("exit\n");
			exit(ft_atoi(input[1]) % 256);
		}
		write(2, "exit\nminishell: exit: ", 22);
		write(2, input[1], ft_strlen(input[1]));
		write(2, ": numeric argument required\n", 28);
		exit(-1 % 256);
	}
}
