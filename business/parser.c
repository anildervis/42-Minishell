#include "../minishell.h"

t_parsed	*new_parse_command(int in_file, int out_file)
{
	t_parsed	*command;

	command = (t_parsed *)malloc(sizeof(t_parsed));
	command->exec = 0;
	command->in_file = in_file;
	command->out_file = out_file;
	command->cmd = ft_calloc(2, sizeof(char));
	command->prev = NULL;
	command->next = NULL;
	command->file_list = NULL;
	command->arguments = ft_calloc(2, sizeof(char *));
	command->paranthesis = NULL;
	return (command);
}

t_parsed	**parse_commands(int in_file, int out_file, t_token *command_table)
{
	t_parsed	**andor_table;
	t_parsed	*command;

	// andor_table = (t_parsed **)malloc(sizeof(t_parsed *) * (andor_count(command_table) + 2));
	andor_table = ft_calloc(andor_count(command_table) + 2, sizeof(t_parsed *));
	while (command_table)
	{
		command = new_parse_command(in_file, out_file);
		if (!command_table->prev)
			command->exec = 3;
		else
			command->exec = command_table->prev->type;
		add_andor_list(command, andor_table);
		while (command_table)
		{
			if (!ft_decide_type(&command_table, &command))
				break ;
		}
	}
	return (andor_table);
}
