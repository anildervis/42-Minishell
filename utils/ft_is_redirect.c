#include "../minishell.h"

int	ft_is_redirect(t_token **command_table)
{
	if ((*command_table)->type == TOKEN_SMALLER
			|| (*command_table)->type == TOKEN_HERE_DOC
			|| (*command_table)->type == TOKEN_GREATER
			|| (*command_table)->type == TOKEN_APPEND)
			return (1);
	return (0);
}
