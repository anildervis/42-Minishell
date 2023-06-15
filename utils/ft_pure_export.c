/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pure_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:50:08 by aderviso          #+#    #+#             */
/*   Updated: 2023/06/15 17:14:37 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_write_begin(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c)
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "=", 1);
}

void	ft_pure_export_print(void)
{
	int		i;
	int		j;
	char	*val;

	i = -1;
	while (g_ms.export[++i])
	{
		write(1, "declare -x ", 11);
		j = 1;
		val = strchr(g_ms.export[i], '=');
		if (val && val != g_ms.export[i])
		{
			ft_write_begin(g_ms.export[i], '=');
			if (!val[1])
				printf("%s\"\"\n", g_ms.export[i]);
			else
				printf("\"%s\"\n", ++val);
		}
		else
			printf("%s\n", g_ms.export[i]);
	}
}
