/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:11:19 by binurtas          #+#    #+#             */
/*   Updated: 2023/06/12 17:08:07 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fd(t_parsed *command)
{
	if (command->in_file != STDIN_FILENO)
		close(command->in_file);
	if (command->out_file != STDOUT_FILENO)
		close(command->out_file);
}

void	close_all_fds(t_parsed **command_table)
{
	t_parsed	**tmp_command_table;
	t_parsed	*tmp_command;
	int			i;

	i = -1;
	tmp_command_table = command_table;
	while (tmp_command_table[++i])
	{
		tmp_command = tmp_command_table[i];
		while (tmp_command)
		{
			if (tmp_command->paranthesis)
				close_all_fds(tmp_command->parantheses_andor);
			else
				close_fd(tmp_command);
			tmp_command = tmp_command->next;
		}
	}
}

int	here_doc_fd(char *limiter)
{
	char	*input;
	char	*final_line;
	int		fd[2];

	input = readline(">");
	final_line = (char *)ft_calloc(2, sizeof(char));
	signal(SIGQUIT, SIG_IGN);
	while (g_ms.ignore && ft_strcmp(limiter, input))
	{
		input = ft_strjoin_freed(input, "\n", 0b10);
		final_line = ft_strjoin_freed(final_line, input, 0b11);
		input = readline(">");
		ctrl_d(str);
	}
	free(input);
	if (pipe(fd) == -1)
		print_error(PIPE_ERR, NULL);
	write(fd[WRITE_END], final_line, ft_strlen(final_line));
	free(final_line);
	close(fd[WRITE_END]);
	return (fd[READ_END]);
}

int	read_file_fd(char *file_name, int type)
{
	if (type == TOKEN_HERE_DOC)
		return (here_doc_fd(file_name));
	if (access(file_name, F_OK) == -1)
		print_error(FILE_NOT_FOUND, file_name);
	else if (access(file_name, R_OK) == -1)
		print_error(PERM_DENIED, file_name);
	return (open(file_name, O_RDONLY, 0666));
}

int	write_file_fd(char *file_name, int type)
{
	int	fd;

	fd = 0;
	if (type == TOKEN_GREATER)
		fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (type == TOKEN_APPEND)
		fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd < 0)
		print_error(FILE_NOT_FOUND, file_name);
	return (fd);
}
