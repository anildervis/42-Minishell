/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:11:10 by binurtas          #+#    #+#             */
/*   Updated: 2023/05/20 14:11:11 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	apply_redirection(t_parsed **command)
{
	t_file	*file_list;

	file_list = (*command)->file_list;
	if (!file_list)
		return ;
	while (file_list)
	{
		if (file_list->type == TOKEN_SMALLER)
			(*command)->in_file = read_file_fd(file_list->file_name,
					file_list->type);
		else if (file_list->type == TOKEN_HERE_DOC)
			(*command)->in_file = read_file_fd(file_list->file_name,
					file_list->type);
		else if (file_list->type == TOKEN_GREATER)
			(*command)->out_file = write_file_fd(file_list->file_name,
					file_list->type);
		else if (file_list->type == TOKEN_APPEND)
			(*command)->out_file = write_file_fd(file_list->file_name,
					file_list->type);
		if ((*command)->in_file < 0 || (*command)->out_file < 0)
			break ;
		file_list = file_list->next;
	}
}

void	create_pipes(t_parsed **command)
{
	int	fd[2];

	while ((*command) && (*command)->next)
	{
		if (pipe(fd) == -1)
		{
			print_error(PIPE_ERR, NULL);
			fd[0] = -1;
			fd[1] = -1;
		}
		if ((*command)->out_file != g_ms.out_file
			&& (*command)->out_file != STDOUT_FILENO)
			close((*command)->out_file);
		(*command)->out_file = fd[WRITE_END];
		if ((*command)->next->in_file != g_ms.out_file
			&& (*command)->next->in_file != STDIN_FILENO)
			close((*command)->next->in_file);
		(*command)->next->in_file = fd[READ_END];
		if ((*command)->next)
			(*command) = (*command)->next;
	}
}

void	create_redirections(t_parsed **andor_table)
{
	int			i;
	t_parsed	*tmp_command;

	i = -1;
	while (andor_table[++i])
	{
		tmp_command = andor_table[i];
		create_pipes(&tmp_command);
		tmp_command = andor_table[i];
		while (tmp_command)
		{
			apply_redirection(&tmp_command);
			if (tmp_command->paranthesis)
			{
				tmp_command->parantheses_andor = parse_commands(
						tmp_command->in_file,
						tmp_command->out_file, tmp_command->paranthesis);
				create_redirections(tmp_command->parantheses_andor);
			}
			tmp_command = tmp_command->next;
		}
	}
}

void	organizer(t_parsed **andor_table)
{
	int			i;
	int			child_count;
	t_parsed	*tmp_command;

	child_count = 0;
	g_ms.child_pids_count = 0;
	i = -1;
	while (andor_table[++i])
	{
		tmp_command = andor_table[i];
		if (organizer_conditions(tmp_command))
		{
			while (tmp_command)
			{
				if (tmp_command->paranthesis)
					child_organizer(tmp_command);
				else
					command_executor(tmp_command);
				tmp_command = tmp_command->next;
			}
		}
	}
	while (child_count < g_ms.child_pids_count)
		waitpid(g_ms.child_pids[child_count++], &errno, 0);
	ft_bzero(g_ms.child_pids, sizeof(int) * g_ms.child_pids_count);
}

void	executor(t_parsed **andor_table)
{
	create_redirections(andor_table);
	organizer(andor_table);
}
