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
