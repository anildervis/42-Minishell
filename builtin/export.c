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
		printf("export index = %d\n", check_export);
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

