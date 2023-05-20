/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:11:25 by binurtas          #+#    #+#             */
/*   Updated: 2023/05/20 14:11:26 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_token(char *input, t_token *command_table, enum tokens type, int len)
{
	t_token	*token;
	t_token	*tmp_table;

	if (type == TOKEN_STR)
		len = token_str_lexer(input);
	token = (t_token *)malloc(sizeof(t_token));
	token = new_token(type, ft_substr(input, 0, len));
	tmp_table = command_table;
	if (!(command_table->value))
	{
		command_table->value = ft_substr(input, 0, len);
		command_table->next = NULL;
		command_table->prev = NULL;
		command_table->type = type;
	}
	else
	{
		while (tmp_table->next)
			tmp_table = tmp_table->next;
		token->prev = tmp_table;
		tmp_table->next = token;
	}
	return (len);
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
	return (command_table);
}

void	get_next_token(t_token *command_table)
{
	t_token	*tmp_command_table;
	t_token	*new_tokens;
	char	*input;

	tmp_command_table = command_table;
	while (tmp_command_table->next)
		tmp_command_table = tmp_command_table->next;
	input = readline("> ");
	new_tokens = tokenizer(input);
	new_tokens->prev = tmp_command_table;
	tmp_command_table->next = new_tokens;
}

int	syntax_check(t_token *ct)
{
	t_token	*tmp;
	int		*p_count;
	int		t_check1;

	tmp = ct;
	p_count = malloc(sizeof(int));
	*p_count = 0;
	while (tmp)
	{
		t_check1 = ft_token_checker(tmp, p_count);
		if (t_check1 != -5)
			return (t_check1);
		if (!tmp->next && *p_count > 0)
		{
			free(p_count);
			get_next_token(tmp);
			return (0);
		}
		tmp = tmp->next;
	}
	free(p_count);
	return (0);
}
