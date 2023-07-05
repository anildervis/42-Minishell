/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:12:15 by binurtas          #+#    #+#             */
/*   Updated: 2023/07/05 13:22:33 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error(int error_code, char *param)
{
	g_ms.error_no = error_code;
	dup2(2, g_ms.out_file);
	syntax_errors(param);
	not_found_errors(param);
	system_errors(param);
	dup2(1, g_ms.out_file);
	if (g_ms.parent_pid != getpid())
		exit(g_ms.error_no);
	return (g_ms.error_no);
}

void	syntax_errors(char *param)
{
	if (g_ms.error_no == SYNTAX_ERROR)
		printf("minishell: syntax error near unexpected token '%s'\n", param);
	else if (g_ms.error_no == UNEXPECTED_EOF)
		printf("minishell: syntax error: unexpected %s\n", param);
}

void	not_found_errors(char *param)
{
	if (g_ms.error_no == FILE_NOT_FOUND)
		printf("minishell: %s: No such file or directory\n", param);
	else if (g_ms.error_no == CMD_NOT_FOUND)
		printf("minishell: %s: command not found\n", param);
}

void	system_errors(char *param)
{
	if (g_ms.error_no == SYSTEM_ERR)
		printf("internal code error\n");
	else if (g_ms.error_no == MEMORY_ERR)
		printf("memory allocation failed\n");
	else if (g_ms.error_no == DUP_ERR)
		printf("could not duplicate fd\n");
	else if (g_ms.error_no == FORK_ERR)
		printf("could not create fork\n");
	else if (g_ms.error_no == PIPE_ERR)
		printf("could not create pipe\n");
	else if (g_ms.error_no == PERM_DENIED)
		printf("permission denied on %s\n", param);
}

void	open_file_error(void)
{
	perror("Failed to open directory");
	exit(EXIT_FAILURE);
}
