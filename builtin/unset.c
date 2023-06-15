/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:12:04 by binurtas          #+#    #+#             */
/*   Updated: 2023/06/15 18:43:54 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_data(int index, char ***array)
{
	int		i;
	int		j;
	char	**new_array;

	i = 0;
	j = 0;
	new_array = ft_calloc(sizeof(char *), ft_get_arg_count(array[0]) + 1);
	while (array[0][i])
	{
		if (index != i)
		{
			new_array[j] = ft_strdup(array[0][i]);
			j++;
		}
		i++;
	}
	free_array(array[0]);
	array[0] = new_array;
}

void	check_remove(char *input)
{
	int	check_env;
	int	check_export;

	check_export = ft_is_exist_export(input);
	check_env = ft_is_exist_env(input);
	if (check_export >= 0)
		remove_data(check_export, &g_ms.export);
	if (check_env >= 0)
		remove_data(check_env, &g_ms.ev);
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
			g_ms.error_no = 1;
			printf("minishell: unset: `%s': not a valid identifier\n", *input);
		}
		else
		{
			data = ft_strjoin(*input, "=");
			check_remove(data);
			free(data);
		}
		input++;
	}
	set_paths();
}
