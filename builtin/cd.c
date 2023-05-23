/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:11:48 by binurtas          #+#    #+#             */
/*   Updated: 2023/05/20 14:11:49 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_working_directories(char *pwd)
{
	set_current_pwd();
	set_old_pwd(pwd);
}

void	builtin_cd(char **execute)
{
	char	*pwd;
	char	*old_pwd;

	pwd = getcwd(0, 0);
	old_pwd = get_env("OLDPWD");
	if (execute[1] && !ft_strcmp(execute[1], "-"))
	{
		if (!(*old_pwd))
			perror("minishell ");
		printf("%s\n", old_pwd);
	}
	else if (execute[1] && ft_strcmp(execute[1], "~"))
	{
		if (chdir(execute[1]))
			perror("minishell ");
		set_working_directories(pwd);
	}
	else
	{
		if (chdir(getenv("HOME")))
			perror("minishell ");
		set_working_directories(pwd);
	}
	free(pwd);
	free(old_pwd);
}
