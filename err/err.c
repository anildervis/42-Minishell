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
	if (errno == FILE_NOT_FOUND)
		printf("minishell: %s: No such file or directory\n", param);
	else if (errno == SYNTAX_ERROR)
		printf("bash: syntax error near unexpected token '%s\n'", param);
	else if (errno == CMD_NOT_FOUND)
		printf("minishell: %s: command not found\n", param);
	else if (errno == PERM_DENIED)
		printf("permission denied on %s\n", param);
	else if (errno == SYSTEM_ERR)
		printf("internal code error\n");
	else if (errno == MEMORY_ERR)
		printf("memory allocation failed\n");
	else if (errno == DUP_ERR)
		printf("could not duplicate fd\n");
	else if (errno == FORK_ERR)
		printf("could not create fork\n");
	else if (errno == PIPE_ERR)
		printf("could not create pipe\n");
	if (g_ms.parent_pid != getpid())
		exit(errno);
	// free minishell ?
	return (errno);
}

void	open_file_error(void)
{
	perror("Failed to open directory");
	exit(EXIT_FAILURE);
}
