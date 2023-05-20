/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:13:03 by binurtas          #+#    #+#             */
/*   Updated: 2023/05/20 14:13:04 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_dir(char *cmd)
{
	DIR	*dir;

	if (!cmd)
		exit(0);
	dir = opendir(cmd);
	if (dir && readdir(dir))
	{
		closedir(dir);
		exit(1);
	}
}

char	*free_new_path(char *np, char *path)
{
	free (np);
	return (path);
}

char	*get_path(char *cmd)
{
	char	*path;
	char	**paths;
	char	*new_cmd;

	check_dir(cmd);
	if (!access(cmd, F_OK))
		return (ft_strdup(cmd));
	paths = g_ms.paths;
	if (!paths)
		print_error(CMD_NOT_FOUND, cmd);
	new_cmd = ft_strjoin("/", cmd);
	while (*paths)
	{
		path = ft_strjoin(*paths, new_cmd);
		if (!access(path, F_OK))
			return (free_new_path(new_cmd, path));
		free(path);
		paths++;
	}
	if (ft_strchr(cmd, '/'))
		print_error(FILE_NOT_FOUND, cmd);
	free(new_cmd);
	return (0);
}
