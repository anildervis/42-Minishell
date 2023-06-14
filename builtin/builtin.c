/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:11:46 by binurtas          #+#    #+#             */
/*   Updated: 2023/06/12 16:57:09 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *command)
{
	if (!ft_strcmp(command, "cd"))
		return (CD);
	else if (!ft_strcmp(command, "env"))
		return (ENV);
	else if (!ft_strcmp(command, "pwd"))
		return (PWD);
	else if (!ft_strcmp(command, "echo"))
		return (ECHO);
	else if (!ft_strcmp(command, "exit"))
		return (EXIT);
	else if (!ft_strcmp(command, "unset"))
		return (UNSET);
	else if (!ft_strcmp(command, "export"))
		return (EXPORT);
	return (0);
}

void	run_builtin(char **exe)
{
	int	type;

	type = is_builtin(exe[0]);
	if (type == CD)
		builtin_cd(exe);
	else if (type == ENV)
		builtin_env();
	else if (type == PWD)
		builtin_pwd();
	else if (type == ECHO)
		builtin_echo(exe);
	else if (type == EXIT)
		builtin_exit(exe);
	else if (type == UNSET)
		builtin_unset(exe);
	else if (type == EXPORT)
		new_builtin_export(exe);
}
