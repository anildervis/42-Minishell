/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pure_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:50:08 by aderviso          #+#    #+#             */
/*   Updated: 2023/06/15 16:00:31 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pure_export_print(void)
{
	int	i;

	i = -1;
	while (g_ms.export[++i])
	{
		printf("declare -x ");
		printf("%s\n", g_ms.export[i]);
	}
}
