/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:12:01 by binurtas          #+#    #+#             */
/*   Updated: 2023/05/20 14:12:02 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(0, 0);
	if (!cwd)
		perror("minishell ");
	else
		printf("%s\n", cwd);
	free(cwd);
	if (g_ms.parent_pid != getpid())
		exit(errno);
}
