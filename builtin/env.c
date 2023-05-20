/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:11:53 by binurtas          #+#    #+#             */
/*   Updated: 2023/05/20 14:11:54 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_env(void)
{
	char	**env;

	env = g_ms.ev;
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	if (g_ms.parent_pid != getpid())
		exit(0);
}
