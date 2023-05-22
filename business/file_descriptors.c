/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:11:19 by binurtas          #+#    #+#             */
/*   Updated: 2023/05/20 15:20:20 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fd(t_parsed *command)
{
	if (command->in_file != g_ms.in_file && command->in_file != STDIN_FILENO)
		close(command->in_file);
	if (command->out_file != g_ms.out_file
		&& command->out_file != STDOUT_FILENO)
		close(command->out_file);
}

//*******While döngüsünün içini kontrol edelim********
int	here_doc_fd(char *limiter)
{
	char	*input;
	char	*final_line;
	char	*tmp;
	int		fd[2];

	input = readline(">");
	final_line = (char *)ft_calloc(2, sizeof(char));
	while (ft_strcmp(limiter, input))
	{
		input = ft_strjoin(input, "\n");
		tmp = final_line;
		final_line = ft_strjoin(final_line, input);
		free(tmp);
		free(input);
		input = readline(">");
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
	if (access(file_name, R_OK) == -1)
		print_error(PERM_DENIED, file_name);
	return (open(file_name, O_RDONLY, 0666));
}

int	write_file_fd(char *file_name, int type)
{
	if (type == TOKEN_GREATER)
		return (open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0666));
	else if (type == TOKEN_APPEND)
		return (open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0666));
	return (-1);
}

void	close_fd_parantheses(t_parsed *command)
{
	int			i;
	t_parsed	*tmp_command;
	t_parsed	**tmp_andor_table;

	if (command->paranthesis)
	{
		tmp_andor_table = command->parantheses_andor;
		i = -1;
		while (tmp_andor_table[++i])
		{
			tmp_command = tmp_andor_table[i];
			while (tmp_command)
			{
				close_fd(tmp_command);
				if (tmp_command->paranthesis)
					close_fd(command);
				tmp_command = tmp_command->next;
			}
		}
	}
}
