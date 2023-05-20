/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:11:48 by binurtas          #+#    #+#             */
/*   Updated: 2023/05/20 14:11:49 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_cd(char **execute)
{
	if (execute[1])
	{
		if (chdir(execute[1]))
			perror("minishell ");
	}
	else
		if (chdir(getenv("HOME")))
			perror("minishell ");
	if (g_ms.parent_pid != getpid())
		exit(errno);
}
