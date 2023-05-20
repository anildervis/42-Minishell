/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:11:46 by binurtas          #+#    #+#             */
/*   Updated: 2023/05/20 14:11:47 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *command)
{
	if (!ft_strcmp(command, "cd"))
		return (CD);
	if (!ft_strcmp(command, "env"))
		return (ENV);
	if (!ft_strcmp(command, "pwd"))
		return (PWD);
	if (!ft_strcmp(command, "echo"))
		return (ECHO);
	if (!ft_strcmp(command, "exit"))
		return (EXIT);
	if (!ft_strcmp(command, "unset"))
		return (UNSET);
	if (!ft_strcmp(command, "export"))
		return (EXPORT);
	return (0);
}

void	run_builtin(char **exe)
{
	int	type;

	type = is_builtin(exe[0]);
	if (type == CD)
		builtin_cd(exe);
	if (type == ENV)
		builtin_env();
	if (type == PWD)
		builtin_pwd();
	if (type == ECHO)
		builtin_echo(exe);
	if (type == EXIT)
		builtin_exit(exe);
	if (type == UNSET)
		builtin_unset(exe);
	if (type == EXPORT)
		builtin_export(exe);
}
