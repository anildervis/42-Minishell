/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:32:26 by aderviso          #+#    #+#             */
/*   Updated: 2023/06/14 13:59:09 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_token(char *input, t_token *command_table, enum e_tokens type, int len)
{
	t_token	*token;
	t_token	*tmp_table;

	if (type == TOKEN_STR)
		len = token_str_lexer(input);
	if (!(command_table->value))
		create_first_token(input, command_table, type, len);
	else
	{
		token = (t_token *)malloc(sizeof(t_token));
		token->type = type;
		token->value = ft_substr(input, 0, len);
		token->next = NULL;
		token->prev = NULL;
		tmp_table = command_table;
		while (tmp_table->next)
			tmp_table = tmp_table->next;
		token->prev = tmp_table;
		tmp_table->next = token;
	}
	return (len);
}

void	create_first_token(char *input, t_token *command_table,
		enum e_tokens type, int len)
{
	command_table->value = ft_substr(input, 0, len);
	command_table->next = NULL;
	command_table->prev = NULL;
	command_table->type = type;
}

void	find_token(char *input, t_token *command_table)
{
	int	i;

	while (*(input))
	{
		i = init_token(input, command_table);
		if (!i)
			input += init_token_continue(input, command_table);
		else
			input += i;
	}
}

t_token	*tokenizer(char *input)
{
	t_token	*command_table;

	command_table = (t_token *)ft_calloc(1, sizeof(t_token));
	find_token(input, command_table);
	g_ms.tokens = command_table;
	return (command_table);
}

void	get_next_token(t_token *command_table)
{
	t_token	*tmp_command_table;
	t_token	*new_tokens;
	char	*input;

	signal(SIGQUIT, SIG_IGN);
	tmp_command_table = command_table;
	while (tmp_command_table->next)
		tmp_command_table = tmp_command_table->next;
	input = readline("> ");
	ctrl_d_as_eof(input);
	if (g_ms.ignore == 1)
		print_error(258, "end of file");
	else if (ft_whitespace_string(input))
	{
		new_tokens = tokenizer(input);
		new_tokens->prev = tmp_command_table;
		tmp_command_table->next = new_tokens;
	}
	free(input);
}
