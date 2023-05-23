/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:12:15 by binurtas          #+#    #+#             */
/*   Updated: 2023/05/20 14:12:16 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// needs to be change by ft_putchar to write into stderror
int	print_error(int error_code, char *param)
{
	errno = error_code;
	syntax_errors(param);
	not_found_errors(param);
	system_errors(param);
	if (g_ms.parent_pid != getpid())
		exit(errno);
	return (errno);
}

void	syntax_errors(char *param)
{
	if (errno == SYNTAX_ERROR)
	{
		perror("bash: syntax error near unexpected token '");
		perror(param);
		perror("'\n");
	}
}

void	not_found_errors(char *param)
{
	if (errno == FILE_NOT_FOUND)
	{
		perror("minishell: ");
		perror(param);
		perror("No such file or directory\n");
	}
	else if (errno == CMD_NOT_FOUND)
	{
		perror("minishell: ");
		perror(param);
		perror("command not found\n");
	}
}

void	system_errors(char *param)
{
	if (errno == SYSTEM_ERR)
		perror("internal code error\n");
	else if (errno == MEMORY_ERR)
		perror("memory allocation failed\n");
	else if (errno == DUP_ERR)
		perror("could not duplicate fd\n");
	else if (errno == FORK_ERR)
		perror("could not create fork\n");
	else if (errno == PIPE_ERR)
		perror("could not create pipe\n");
	else if (errno == PERM_DENIED)
	{
		perror("permission denied on ");
		perror(param);
		perror("\n");
	}
}

void	open_file_error(void)
{
	perror("Failed to open directory");
	exit(EXIT_FAILURE);
}
