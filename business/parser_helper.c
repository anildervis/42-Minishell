#include "../minishell.h"

int	ft_decide_type(t_token **command_table, t_parsed **command)
{
	if ((*command_table)->type == TOKEN_AND
		|| (*command_table)->type == TOKEN_OR)
	{
		(*command_table) = (*command_table)->next;
		return (0);
	}
	else if (ft_is_redirect(command_table))
	{
		add_redirection(command_table, command);
	}
	else if ((*command_table)->type == TOKEN_OPEN_PAR)
	{
		add_paranthesis(command_table, command);
	}
	else if ((*command_table)->type == TOKEN_STR)
	{
		add_argument(command_table, command);
	}
	else if ((*command_table)->type == TOKEN_PIPE)
	{
		*command = add_parse(command_table, command);
	}
	return (1);
}

void	add_andor_list(t_parsed *command, t_parsed **andor_table)
{
	int	i;

	i = 0;
	while (andor_table[i])
		i++;
	andor_table[i] = command;
	andor_table[i + 1] = NULL;
}

void	skip_paranthesis(t_token **command_table)
{
	int	i;

	i = 0;
	while ((*command_table))
	{
		if ((*command_table)->type == TOKEN_OPEN_PAR)
			i++;
		else if ((*command_table)->type == TOKEN_CLOSE_PAR)
			i--;
		if (!i)
			break ;
		(*command_table) = (*command_table)->next;
	}
	// error;
}

int	andor_count(t_token *command_table)
{
	int		i;
	t_token	*tmp_list;

	i = 0;
	tmp_list = command_table;
	while (tmp_list)
	{
		if (tmp_list->type == TOKEN_AND || tmp_list->type == TOKEN_OR)
			i++;
		else if (tmp_list->type == TOKEN_OPEN_PAR)
			skip_paranthesis(&tmp_list);
		tmp_list = tmp_list->next;
	}
	return (i);
}