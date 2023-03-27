#include "minishell.h"

int andor_count(t_token *command_table)
{
	int i;
	t_token	*tmp_list;

	i = 0;
	tmp_list = command_table;
	while (tmp_list->next)
	{
		if (tmp_list->type == TOKEN_AND
			|| tmp_list->type == TOKEN_OR)
			i++;
		else if (tmp_list->type == TOKEN_OPEN_PAR)
			skip_paranthesis(&tmp_list);
		tmp_list = tmp_list->next;
	}
	printf("andor count -> %d\n", i);
	return i;
}

t_parsed *new_parse_command(int in_file, int out_file)
{
	t_parsed	*command;

	command = (t_parsed *)malloc(sizeof(t_parsed));
	command->exec = 0;
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

	i = 0;
	while (andor_table[i])	
		i++;
	andor_table[i] = command;
	andor_table[i + 1] = NULL;
}

void add_redirection(t_token **command_table, t_parsed **command)
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
		if (!i)
			break;
		(*command_table) = (*command_table)->next;
	}
	// error;
}

t_parsed *add_parse(t_token **command_table, t_parsed **old_command)
{
	t_parsed *new_command;

	new_command = new_parse_command((*old_command)->in_file, (*old_command)->out_file);
	printf("here\n");
	(*old_command)->next = new_command;
	new_command->prev = (*old_command);
	(*command_table) = (*command_table)->next;
	return (new_command);
}

void add_argument(t_token **command_table, t_parsed **command)
{
	int	i;
	char **new_arguments;

	i = 0;
	if (!((*command)->cmd))
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
	(*command)->arguments = new_arguments;
	(*command_table) = (*command_table)->next;
}

void add_paranthesis(t_token **command_table, t_parsed **command)
{
	int i;
    t_token *paranthesis_command_table;

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
		add_token((*command_table)->value, (*command)->paranthesis, (*command_table)->type, 2);
		(*command_table) = (*command_table)->next;
	}
	(*command_table) = (*command_table)->next;
}

t_parsed	**parse_commands(int in_file, int out_file, t_token *command_table)
{
	t_parsed	**andor_table;
	t_parsed	*command;

	andor_table = (t_parsed **)malloc(sizeof(t_parsed *) * (andor_count(command_table) + 1));
	while (command_table)
	{
		printf("inside\n");
		command = new_parse_command(in_file, out_file);
		if (!command_table->prev)
			command->exec = 3;
		else
			command->exec = command_table->prev->type;
		printf("infile -> %d, outfile -> %d\n", command->in_file, command->out_file);
		add_andor_list(command_table->type, command, andor_table);
		while (command_table)
		{
			printf("inception? type -> %d\n", command_table->type);
			if (command_table->type == TOKEN_AND
				|| command_table->type == TOKEN_OR)
			{
				(command_table) = (command_table)->next;
				break ;
			}
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
	return (andor_table);
}