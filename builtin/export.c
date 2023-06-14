/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:11:59 by binurtas          #+#    #+#             */
/*   Updated: 2023/06/12 20:50:26 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_update_export(int index, char *input)
{
	free(g_ms.export[index]);
	g_ms.export[index] = ft_strdup(input);
}

void	ft_update_env(int index, char *input)
{
	free(g_ms.ev[index]);
	g_ms.ev[index] = ft_strdup(input);
}

void	new_builtin_export(char **input)
{
	int check_env;
	int check_export;
	int i;

	if (!input[1])
		ft_pure_export_print();
	i = 1;
	while (input[i])
	{
		if (check_char(input[0], input[i]))
		{
			i++;
			continue ;
		}
		check_export = ft_is_exist_export(input[i]);
		check_env = ft_is_exist_env(input[i]);
		if (is_there_equal(input[i]))
		{
			if (check_export >= 0)
				ft_update_export(check_export, input[i]);
			else
				add_export(input[i]);
			if (check_env >= 0)
				ft_update_env(check_env, input[i]);
			else
				add_env(input[i]);
		}
		else
		{
			if (check_export >= 0)
				ft_update_export(check_export, input[i]);
			else
				if (check_export != -2)
					add_export(input[i]);
		}
		i++;
	}
}

void	add_env(char *input)
{
	int		i;
	char	**new_env;

	i = -1;
	new_env = ft_calloc(sizeof(char *), ft_get_arg_count(g_ms.ev) + 2);
	while (g_ms.ev[++i])
		new_env[i] = ft_strdup(g_ms.ev[i]);
	new_env[i] = ft_strdup(input);
	free_array(g_ms.ev);
	g_ms.ev = new_env;
}

void	add_export(char *input)
{
	char	**new_export;
	int		i;

	i = -1;
	new_export = ft_calloc(sizeof(char *), ft_get_arg_count(g_ms.export) + 2);
	while (g_ms.export[++i])
		new_export[i] = ft_strdup(g_ms.export[i]);
	new_export[i] = ft_strdup(input);
	free_array(g_ms.export);
	g_ms.export = new_export;
	ft_sort_export();
}

void	ft_sort_export(void)
{
	char	*tmp;
	int		i;
	int		j;
	int		size;

	i = 0;
	size = ft_get_arg_count(g_ms.export);
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(g_ms.export[i], g_ms.export[j]) > 0)
			{
				tmp = g_ms.export[i];
				g_ms.export[i] = g_ms.export[j];
				g_ms.export[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
