#include "../minishell.h"

int	init_token(char *input, t_token *command_table)
{
	char	*tmp;

	tmp = input;
	if (*(input) == '&' && *(input + 1) == '&')
		input += add_token(input, command_table, TOKEN_AND, 2);
	else if (*(input) == '(')
		input += add_token(input, command_table, TOKEN_OPEN_PAR, 1);
	else if (*(input) == ')')
		input += add_token(input, command_table, TOKEN_CLOSE_PAR, 1);
	else if (*(input) == '|')
	{
		if (*(input + 1) == '|')
			input += add_token(input, command_table, TOKEN_OR, 2);
		else
			input += add_token(input, command_table, TOKEN_PIPE, 1);
	}
	return (input - tmp);
}

int	init_token_continue(char *input, t_token *command_table)
{
	char	*tmp;

	tmp = input;
	if (*(input) == '>')
	{
		if (*(input + 1) == '>')
			input += add_token(input, command_table, TOKEN_APPEND, 2);
		else
			input += add_token(input, command_table, TOKEN_GREATER, 1);
	}
	else if (*(input) == '<')
	{
		if (*(input + 1) == '<')
			input += add_token(input, command_table, TOKEN_HERE_DOC, 2);
		else
			input += add_token(input, command_table, TOKEN_SMALLER, 1);
	}
	else if (*(input) == ' ' || *(input) == '\t' || *(input) == '\n')
		input += 1;
	else
		input += add_token(input, command_table, TOKEN_STR, 0);
	return (input - tmp);
}
