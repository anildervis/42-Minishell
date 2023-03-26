#include "minishell.h"

int andor_count(t_token *command_table)
{
	int i;

	i = 0;
	while (command_table)
	{
		if (command_table->type == TOKEN_AND
			|| command_table->type == TOKEN_OR)
			i++;
		command_table->next;
	}
}

t_parsed *new_parse_command(int in_file, int out_file)
{
	t_parsed	*command;

	command = (t_parsed *)malloc(sizeof(t_parsed));
	command->in_file = in_file;
	command->out_file = out_file;
	command->cmd = NULL;
	command->prev = NULL;
	command->next = NULL;
	command->file_list = NULL;
	command->arguments = NULL;
	command->paranthesis = NULL;
	return (command);
}

void add_andor_list(enum tokens andor, t_parsed *command, t_parsed **andor_table)
{
	int i;

	i = -1;
	while (andor_table[i])	
		i++;
	andor_table[i] = command;
}

void add_redirection(t_token **command_table, t_parsed **command)
{
	t_file	*file_list;
	t_file	*tmp_list;

	tmp_list = (*command)->file_list;
	file_list = (t_file *)malloc(sizeof(t_file));
	file_list->next = NULL;
	file_list->type == (*command_table)->type;
	(*command_table) = (*command_table)->next;
	file_list->file_name = (*command_table)->value; // if there is?
	if (!tmp_list)
		tmp_list = file_list;
	else
	{
		while (tmp_list->next)
			tmp_list = tmp_list->next;
		tmp_list->next = file_list;
	}
	(*command_table) = (*command_table)->next;
}

void skip_paranthesis(t_token **command_table)
{
	int i;

	i = 0;
	while ((*command_table))
	{
		if ((*command_table)->type == TOKEN_OPEN_PAR)
			i++;
		else if ((*command_table)->type == TOKEN_CLOSE_PAR)
			i--;
		(*command_table) = (*command_table)->next;
		if (!i)
			break;
	}
	// error;
}

t_parsed *add_parse(t_token **command_table, t_parsed **old_command)
{
	t_parsed *new_command;

	new_command = new_parse_command((*old_command)->in_file, (*old_command)->out_file);
	(*old_command)->next = new_command;
	new_command->prev = (*old_command);
	return (new_command);
}

void add_argument(t_token **command_table, t_parsed **command)
{
	int	i;
	char **new_arguments;

	i = 0;
	if (!((*command)->cmd))
		(*command)->cmd = (*command_table)->value;
	while ((*command)->arguments[i])
		i++;
	new_arguments = (char **)malloc(sizeof(char *) * (i + 2));
	new_arguments[i + 1] = NULL;
	new_arguments[i] = (*command_table)->value;
	while (i--)
	{
		new_arguments[i] = ft_strdup((*command)->arguments[i]);
		free((*command)->arguments[i]);
	}
	free((*command)->arguments);
	(*command)->arguments = new_arguments;
}

void add_paranthesis(t_token **command_table, t_parsed **command)
{
	int i;

	i = 1;
	(*command_table) = (*command_table)->next;
	while (*command_table && i != 0)
	{
		if ((*command_table)->next->type == TOKEN_OPEN_PAR)
			i++;
		else if ((*command_table)->next->type == TOKEN_CLOSE_PAR)
			i--;
		add_token((*command_table)->value, (*command)->paranthesis, (*command_table)->type, ft_strlen((*command_table)->type));
	}
	(*command_table) = (*command_table)->next->next;
}

t_parsed	**parse_commands(int in_file, int out_file, t_token *command_table)
{
	t_parsed	**andor_table;
	t_parsed	*command;

	andor_table = (t_parsed **)malloc(sizeof(t_parsed *) * andor_count(command_table));
	while (command_table && command_table->type != TOKEN_CLOSE_PAR)
	{
		command = new_parse_command(in_file, out_file);
		add_andor_list(command_table->type, command, andor_table);
		while (command_table && command_table->type != TOKEN_CLOSE_PAR)
		{
			if (command_table->type == TOKEN_AND
				|| command_table->type == TOKEN_OR)
				break ;
			else if (command_table->type == TOKEN_SMALLER
				|| command_table->type == TOKEN_HERE_DOC
				|| command_table->type == TOKEN_GREATER
				|| command_table->type == TOKEN_APPEND)
				add_redirection(&command_table, &command);
			else if (command_table->type == TOKEN_OPEN_PAR)
				add_paranthesis(&command_table, &command);
			else if (command_table->type == TOKEN_STR)
				add_argument(&command_table, &command);
			else if (command_table->type == TOKEN_PIPE)
				command = add_parse(&command_table, &command);
		}
	}
}