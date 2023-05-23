/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:12:04 by binurtas          #+#    #+#             */
/*   Updated: 2023/05/20 14:12:05 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_env(char *data)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = ft_calloc(sizeof(char *), env_len() + 1);
	while (g_ms.ev[i])
	{
		if (ft_strncmp(g_ms.ev[i], data, ft_strlen(data)))
		{
			new_env[j] = ft_strdup(g_ms.ev[i]);
			j++;
		}
		i++;
	}
	new_env[j] = 0;
	free_array(g_ms.ev);
	g_ms.ev = new_env;
}

void	builtin_unset(char **input)
{
	char	*data;

	input++;
	while (*input)
	{
		if (ft_strchr(*input, '='))
		{
			errno = 1;
			printf("minishell: unset: `%s': not a valid identifier\n", *input);
		}
		else
		{
			data = ft_strjoin(*input, "=");
			remove_env(data);
			free(data);
		}
		input++;
	}
	set_paths();
}
