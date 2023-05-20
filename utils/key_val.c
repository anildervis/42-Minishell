/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_val.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:13:11 by binurtas          #+#    #+#             */
/*   Updated: 2023/05/20 14:13:12 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		addenv(char *key, char *val)
{
	int		i;
	int		len;
	char	**envs;

	// if (!key || !val)
	// 	ft_err(EADDPATH);
	len = 0;
	while (g_ms.ev[len])
		len++;
	envs = malloc(sizeof(char *) * (len + 2));
	if (!envs)
		return (0);
	i = -1;
	while (g_ms.ev[++i])
		envs[i] = ft_strdup(g_ms.ev[i]);
	envs[i] = ft_strjoin(key, val);
	envs[i + 1] = 0;
	g_ms.ev = envs;
	return (1);
}
