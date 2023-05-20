/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:11:02 by binurtas          #+#    #+#             */
/*   Updated: 2023/05/20 14:20:37 by binurtas         ###   ########.fr       */
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
		if ((*command_table)->next->type == TOKEN_OPEN_PAR)
			i++;
		else if ((*command_table)->next->type == TOKEN_CLOSE_PAR)
			i--;
		add_token((*command_table)->value, (*command)->paranthesis,
			(*command_table)->type, 2);
		(*command_table) = (*command_table)->next;
	}
	(*command_table) = (*command_table)->next;
}

/*
tokenlar command olurken her komutun kendi argümanları oluşuyor.
exmp : echo "bilal" > bilal
burada echo bir komut ve argümanları "echo" "bilal" şeklinde iki char arrayi oluyor.
*/
void	add_argument(t_token **command_table, t_parsed **command)
{
	int		i;
	char	**new_arguments;

	i = 0;
	if (!(*(*command)->cmd))
	{
		(*command)->cmd = (*command_table)->value;
		(*command)->arguments = (char **)ft_calloc(2, sizeof(char *));
	}
	while ((*command)->arguments[i])
		i++;
	new_arguments = (char **)malloc(sizeof(char *) * (i + 2));
	new_arguments[i + 1] = NULL;
	new_arguments[i] = (*command_table)->value;
	while (i--)
		new_arguments[i] = ft_strdup((*command)->arguments[i]);
	// free old arguments
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

/*
echo bilal > bilal için:
> tokenda(greater) bu fonksiyon çalışacak ve echo komutumuz için bir file list oluşacak.
echo komutunun file listi bu fonksiyon bittikten sonra
file_list->type = greater
file_list->file_name = bilal (bu bilal greater tokenından ardından gelen bilal)
*/
void	add_redirection(t_token **command_table, t_parsed **command)
{
	t_file	*file_list;
	t_file	*tmp_list;

	tmp_list = (*command)->file_list;
	file_list = (t_file *)malloc(sizeof(t_file));
	file_list->next = NULL;
	file_list->type = (*command_table)->type;
	(*command_table) = (*command_table)->next;
	file_list->file_name = (*command_table)->value; // if there is?
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
