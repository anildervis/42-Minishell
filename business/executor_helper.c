/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:11:07 by binurtas          #+#    #+#             */
/*   Updated: 2023/06/15 18:44:56 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	command_executor(t_parsed *command, int i)
{
	if (command->in_file == -1 || command->out_file == -1)
		return ;
	if (!(command->cmd) || !ft_strlen(command->cmd))
		return ;
	expander(&command);
	builtin_conditions(command, i);
}

void	builtin_conditions(t_parsed *command, int i)
{
	pid_t	pid;

	if (is_builtin(command->cmd))
	{
		if (g_ms.parsed_commands[i]->next)
		{
			pid = fork();
			g_ms.child_pids[g_ms.child_pids_count++] = pid;
			if ((pid) < 0)
				print_error(FORK_ERR, NULL);
			if (!pid)
			{
				execute_builtin(command);
				exit(g_ms.error_no);
			}
			usleep(10000);
			close_fd(command);
		}
		else
			execute_builtin(command);
	}
	else
		execute_not_builtin(command);
}

void	execute_builtin(t_parsed *command)
{
	int		in;
	int		out;

	g_ms.error_no = 0;
	in = dup(g_ms.in_file);
	out = dup(g_ms.out_file);
	dup2(command->in_file, STDIN_FILENO);
	dup2(command->out_file, STDOUT_FILENO);
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
	char	*command_path;

	pid = fork();
	g_ms.child_pids[g_ms.child_pids_count++] = pid;
	signal(SIGINT, &ctrl_c_inside_child);
	if ((pid) < 0)
		print_error(FORK_ERR, NULL);
	if (!pid)
	{
		g_ms.error_no = 0;
		if (command->prev && command->prev->out_file != STDOUT_FILENO)
			close(command->prev->out_file);
		if (command->next && command->next->in_file != STDIN_FILENO)
			close(command->next->in_file);
		dup2(command->in_file, STDIN_FILENO);
		dup2(command->out_file, STDOUT_FILENO);
		close_all_fds(g_ms.parsed_commands);
		command_path = get_path(command->cmd);
		execve(command_path, command->arguments, g_ms.ev);
		free(command_path);
		print_error(CMD_NOT_FOUND, command->cmd);
		exit(g_ms.error_no);
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
		if (command->next && command->next->in_file != g_ms.in_file)
			close(command->next->in_file);
		if (command->prev && command->prev->out_file != g_ms.out_file)
			close(command->prev->out_file);
		g_ms.in_file = command->in_file;
		g_ms.out_file = command->out_file;
		executor(command->parantheses_andor);
		close_all_fds(g_ms.parsed_commands);
		exit(g_ms.error_no);
	}
	usleep(10000);
	close_fd(command);
	close_all_fds(command->parantheses_andor);
}
