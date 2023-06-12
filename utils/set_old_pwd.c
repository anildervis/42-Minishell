/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_old_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:23:18 by binurtas          #+#    #+#             */
/*   Updated: 2023/06/12 14:23:19 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_old_pwd(char *pwd)
{
	char	**command;

	command = malloc(sizeof(char *) * 3);
	if (!command)
		return ;
	command[0] = ft_strdup("export");
	command[1] = ft_strjoin("OLDPWD=", pwd);
	command[2] = 0;
	builtin_export(command);
	free_array(command);
}
