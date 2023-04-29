#include "../minishell.h"

t_token	*new_token(enum tokens type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->type = type;
	token->value = value;
	token->next = 0;
	token->prev = 0;
	return (token);
}
