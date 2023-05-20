/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:13:19 by binurtas          #+#    #+#             */
/*   Updated: 2023/05/20 14:13:20 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**set_ev(char **ev)
{
	int		i;
	char	**msev;

	i = 0;
	while (ev[i])
		i++;
	msev = malloc(sizeof(char *) * (i + 1));
	if (!msev)
		return (0);
	i = -1;
	while (ev[++i])
		msev[i] = ft_strdup(ev[i]);
	msev[i] = 0;
	return (msev);
}
