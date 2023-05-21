/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:11:07 by binurtas          #+#    #+#             */
/*   Updated: 2023/05/20 14:11:08 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	command_executor(t_parsed *command)
{
	expander(&command);
	if (is_builtin(command->cmd))
		execute_builtin(command);
	else
		execute_not_builtin(command);
}

void	execute_builtin(t_parsed *command)
{
	int		in;
	int		out;

	errno = 0;
	in = dup(g_ms.in_file);
	out = dup(g_ms.out_file);
	dup2(command->in_file, g_ms.in_file);
	dup2(command->out_file, g_ms.out_file);
	run_builtin(command->arguments);
	close_fd(command);
	dup2(in, g_ms.in_file);
	dup2(out, g_ms.out_file);
	close(in);
	close(out);
}

void	execute_not_builtin(t_parsed *command)
{
	pid_t	pid;

	pid = fork();
	g_ms.child_pids[g_ms.child_pids_count++] = pid;
	if ((pid) < 0)
		print_error(FORK_ERR, NULL);
	if (!pid)
	{
		errno = 0;
		if (command->prev && command->prev->out_file != STDOUT_FILENO)
			close(command->prev->out_file);
		if (command->next && command->next->in_file != STDIN_FILENO)
			close(command->next->in_file);
		dup2(command->in_file, STDIN_FILENO);
		dup2(command->out_file, STDOUT_FILENO);
		close_fd(command);
		execve(get_path(command->cmd), command->arguments, g_ms.ev);
		print_error(CMD_NOT_FOUND, command->cmd);
		exit(errno);
	}
	usleep(10000);
	close_fd(command);
}

void	child_organizer(t_parsed *command)
{
	pid_t	pid;

	pid = fork();
	g_ms.child_pids[g_ms.child_pids_count++] = pid;
	if (pid < 0)
		print_error(FORK_ERR, NULL);
	if (!pid)
	{
		g_ms.parent_pid = getpid();
		if (command->prev && command->prev->out_file != STDOUT_FILENO)
			close(command->prev->out_file);
		if (command->next && command->next->in_file != STDIN_FILENO)
			close(command->next->in_file);
		g_ms.in_file = command->in_file;
		g_ms.out_file = command->out_file;
		organizer(command->parantheses_andor);
		close_fd(command);
		exit(0);
	}
	usleep(10000);
	close_fd(command);
	close_fd_parantheses(command);
}

int	organizer_conditions(t_parsed *tmp_command)
{
	if (tmp_command->exec == 3 || (tmp_command->exec == TOKEN_AND
			&& errno == 0) || (tmp_command->exec == TOKEN_OR && errno != 0))
		return (1);
	return (0);
}