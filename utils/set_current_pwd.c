/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_current_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:22:52 by binurtas          #+#    #+#             */
/*   Updated: 2023/06/15 16:35:53 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_current_pwd(void)
{
	char	**command;

	command = malloc(sizeof(char *) * 3);
	if (!command)
		return ;
	command[0] = ft_strdup("export");
	command[1] = ft_strjoin_freed("PWD=", getcwd(0, 0), 0b01);
	command[2] = 0;
	builtin_export(command);
	free_array(command);
}
