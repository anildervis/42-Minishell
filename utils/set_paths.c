/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:13:22 by binurtas          #+#    #+#             */
/*   Updated: 2023/05/20 14:13:23 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_paths(void)
{
	char	*path;

	if (g_ms.paths)
		free_array(g_ms.paths);  // yapmasam leak mi oluşur ???
	path = get_env("PATH");
	if (!(*path))
		g_ms.paths = 0;
	else
		g_ms.paths = ft_split(path, ':');
	free(path);
}
