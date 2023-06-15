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
	new_env = ft_calloc(sizeof(char *), ft_get_arg_count(g_ms.ev) + 1);
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
		if (check_char(input[0], *input) && input++)
			continue ;
		if (ft_strchr(*input, '='))
		{
			errno = 1;
			printf("minishell: unset: `%s': not a valid identifier\n", *input);
		}
		else
		{
			data = ft_strjoin(*input, "=");
			check_remove(data);
			remove_env(data);
			free(data);
		}
		input++;
	}
	set_paths();
}

void	check_remove(char *input)
{
	int	check_env;
	int	check_export;

	check_export = ft_is_exist_export(input);
	check_env = ft_is_exist_env(input);
	if (check_export >= 0)
		ft_remove_export(check_export);
	if (check_env >= 0)
		ft_remove_env(check_env);
}
