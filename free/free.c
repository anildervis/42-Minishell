/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:12:18 by binurtas          #+#    #+#             */
/*   Updated: 2023/05/20 14:12:19 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(t_token *tokens, t_parsed **parsed_commands)
{
	free_tokens(tokens);
	free_parsed(parsed_commands);
}

void	free_tokens(t_token *tokens)
{
	t_token *tmp;
	t_token *to_free;

	tmp = tokens;
	while (tmp)
	{
		to_free = tmp;
		free(tmp->value);
		tmp = tmp->next;
		free(to_free);
	}
}

void	free_parsed(t_parsed **parsed_commands)
{
	t_parsed **tmp_list;
	t_parsed *tmp_command;
	t_parsed *to_free;
	int i;

	tmp_list = parsed_commands;
	i = -1;
	while (tmp_list[++i])
	{
		tmp_command = tmp_list[i];
		while (tmp_command)
		{
			to_free = tmp_command;
			free_redirections(tmp_command->file_list);
			if (tmp_command->paranthesis)
				free_tokens(tmp_command->paranthesis);
			else
			{
				free(tmp_command->cmd);
				free_array(tmp_command->arguments);
			}
			tmp_command = tmp_command->next;
			free(to_free);
		}
	}
	free(tmp_list);
}

void	free_redirections(t_file *file_list)
{
	t_file *tmp;
	t_file *to_free;

	tmp = file_list;
	if (tmp != NULL)
	{
		to_free = tmp;
		free(tmp->file_name);
		tmp = tmp->next;
		free(to_free);
	}
}

void	free_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}
