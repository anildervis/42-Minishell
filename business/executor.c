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
		file_list = file_list->next;
	}
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

void	command_executor(t_parsed *command)
{
	pid_t	pid;
	int		in;
	int		out;

	expander(&command);
	if (is_builtin(command->cmd))
	{
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
	else
	{
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
}

void	create_pipe(t_parsed **command)
{
	int	fd[2];

	if (pipe(fd) == -1)
		print_error(PIPE_ERR, NULL);
	if ((*command)->out_file != g_ms.out_file
		&& (*command)->out_file != STDOUT_FILENO)
		close((*command)->out_file);
	(*command)->out_file = fd[WRITE_END];
	if ((*command)->next->in_file != g_ms.out_file
		&& (*command)->next->in_file != STDIN_FILENO)
		close((*command)->next->in_file);
	(*command)->next->in_file = fd[READ_END];
}

void	create_redirections(t_parsed **andor_table)
{
	int			i;
	t_parsed	*tmp_command;

	i = -1;
	while (andor_table[++i])
	{
		tmp_command = andor_table[i];
		while (tmp_command)
		{
			if (tmp_command->next)
				create_pipe(&tmp_command);
			apply_redirection(&tmp_command);
			if (tmp_command->paranthesis)
			{
				tmp_command->parantheses_andor = parse_commands(tmp_command->in_file,
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
		if (tmp_command->exec == 3 || (tmp_command->exec == TOKEN_AND
				&& errno == 0) || (tmp_command->exec == TOKEN_OR && errno != 0))
			while (tmp_command)
			{
				if (tmp_command->paranthesis)
					child_organizer(tmp_command);
				else
					command_executor(tmp_command);
				tmp_command = tmp_command->next;
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
