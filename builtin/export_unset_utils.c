/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:19:48 by binurtas          #+#    #+#             */
/*   Updated: 2023/07/05 13:23:47 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_char(char *cmd, char *input)
{
	int	i;
	int	check_special;

	i = 0;
	while (input[i])
	{
		check_special = ft_special_finder(input);
		if (check_special || ft_is_numeric(input[0])
			|| input[0] == '=')
		{
			g_ms.error_no = 1;
			printf("minishell: %s: %s: not a valid identifier\n", cmd, input);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_is_exist_export(char *input)
{
	int	i;
	int	j;

	i = -1;
	while (g_ms.export[++i])
	{
		j = 0;
		while (g_ms.export[i][j] && input[j])
		{
			if (input[j] == '=' && g_ms.export[i][j] == '=')
				return (i);
			if (input[j] != g_ms.export[i][j])
				break ;
			if (!input[j + 1] && !g_ms.export[i][j + 1]
				&& input[j] == g_ms.export[i][j])
				return (i);
			j++;
		}
		if (!input[j] && g_ms.export[i][j] == '=')
			return (-2);
		if (!g_ms.export[i][j] && input[j] == '='
			&& g_ms.export[i][j - 1] == input[j - 1])
			return (i);
	}
	return (-1);
}

int	ft_is_exist_env(char *input)
{
	int	i;
	int	j;

	i = -1;
	while (g_ms.ev[++i])
	{
		j = 0;
		while (g_ms.ev[i][j] && input[j])
		{
			if (input[j] == '=' && g_ms.ev[i][j] == '=')
				return (i);
			if (input[j] != g_ms.ev[i][j])
				break ;
			j++;
		}
	}
	return (-1);
}

int	is_there_equal(char *input)
{
	char	*head;

	head = ft_strchr(input, '=');
	if (head && head != input)
		return (1);
	return (0);
}
