/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:11:59 by binurtas          #+#    #+#             */
/*   Updated: 2023/06/15 17:39:42 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_there_is_equal(int c_export, int c_env, char *input)
{
	if (c_export >= 0)
		ft_update_export(c_export, input);
	else
		add_export(input);
	if (c_env >= 0)
		ft_update_env(c_env, input);
	else
		add_env(input);
}

void	ft_no_equal(int c_export, char *input)
{
	if (c_export >= 0)
		ft_update_export(c_export, input);
	else
		if (c_export != -2)
			add_export(input);
}

void	builtin_export(char **input)
{
	int	check_env;
	int	check_export;
	int	i;

	if (!input[1])
		ft_pure_export_print();
	i = 1;
	while (input[i])
	{
		if (check_char(input[0], input[i]) && i++)
			continue ;
		check_export = ft_is_exist_export(input[i]);
		check_env = ft_is_exist_env(input[i]);
		if (is_there_equal(input[i]))
			ft_there_is_equal(check_export, check_env, input[i]);
		else
			ft_no_equal(check_export, input[i]);
		i++;
	}
}
