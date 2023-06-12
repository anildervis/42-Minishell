/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:11:02 by binurtas          #+#    #+#             */
/*   Updated: 2023/06/12 14:57:44 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_paranthesis(t_token **command_table, t_parsed **command)
{
	int		i;
	t_token	*paranthesis_command_table;

	i = 1;
	paranthesis_command_table = (t_token *)ft_calloc(1, sizeof(t_token));
	(*command)->paranthesis = paranthesis_command_table;
	(*command_table) = (*command_table)->next;
	while (*command_table && i != 0)
	{
		if ((*command_table)->type == TOKEN_OPEN_PAR)
			i++;
		else if ((*command_table)->type == TOKEN_CLOSE_PAR)
			i--;
		if (i != 0)
			add_token((*command_table)->value, (*command)->paranthesis,
				(*command_table)->type, 2);
		(*command_table) = (*command_table)->next;
	}
}

void	add_argument(t_token **command_table, t_parsed **command)
{
	int		i;
	char	**new_arguments;

	i = 0;
	if (!((*command)->cmd))
	{
		(*command)->cmd = ft_calloc(ft_strlen((*command_table)->value) + 2,
				sizeof(char));
		ft_strcpy((*command)->cmd, (*command_table)->value);
		(*command)->arguments = ft_calloc(2, sizeof(char *));
	}
	while ((*command)->arguments[i])
		i++;
	new_arguments = ft_calloc((i + 2), sizeof(char *));
	new_arguments[i + 1] = NULL;
	new_arguments[i] = ft_strdup((*command_table)->value);
	while (i--)
		new_arguments[i] = ft_strdup((*command)->arguments[i]);
	free_array((*command)->arguments);
	(*command)->arguments = new_arguments;
	(*command_table) = (*command_table)->next;
}

t_parsed	*add_parse(t_token **command_table, t_parsed **old_command)
{
	t_parsed	*new_command;

	new_command = new_parse_command((*old_command)->in_file,
			(*old_command)->out_file);
	(*old_command)->next = new_command;
	new_command->prev = (*old_command);
	(*command_table) = (*command_table)->next;
	return (new_command);
}

void	add_redirection(t_token **command_table, t_parsed **command)
{
	t_file	*file_list;
	t_file	*tmp_list;

	tmp_list = (*command)->file_list;
	file_list = (t_file *)malloc(sizeof(t_file));
	file_list->next = NULL;
	file_list->type = (*command_table)->type;
	(*command_table) = (*command_table)->next;
	file_list->file_name = (*command_table)->value;
	if (!tmp_list)
		(*command)->file_list = file_list;
	else
	{
		while (tmp_list->next)
			tmp_list = tmp_list->next;
		tmp_list->next = file_list;
	}
	(*command_table) = (*command_table)->next;
}
