/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:41:04 by aderviso          #+#    #+#             */
/*   Updated: 2023/06/12 20:12:13 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	not_paired(char **str, int *i)
{
	char	*input;
	char	*final_str;

	final_str = ft_strjoin_freed(ft_strdup(*str), "\n", 0b10);
	input = readline("> ");
	while (!ft_strchr(input, *(*str + *i)))
	{
		final_str = ft_strjoin_freed(final_str, input, 0b11);
		input = readline("> ");
		final_str = ft_strjoin_freed(final_str, "\n", 0b10);
	}
	final_str = ft_strjoin_freed(final_str, input, 0b11);
	free(*str);
	*str = final_str;
	*i += find_pair(*str + *i, *(*str + *i)) + 1;
}

void	adding_new_tokens_to_list(t_token *command_table, char *str)
{
	t_token	*new_tokens;
	t_token	*end;

	new_tokens = tokenizer(str);
	free(command_table->value);
	command_table->value = ft_strdup(new_tokens->value);
	end = command_table->next;
	command_table->next = new_tokens->next;
	while (command_table->next)
		command_table = command_table->next;
	command_table->next = end;
	if (end)
		end->prev = command_table;
	free(new_tokens->value);
	free(new_tokens);
}

void	string_completer(t_token *command_table)
{
	char	*str;
	int		i;

	str = ft_strdup(command_table->value);
	i = -1;
	while (*(str + ++i))
	{
		if (*(str + i) == *DOUBLE_QUOTE || *(str + i) == *SINGLE_QUOTE)
		{
			if (find_pair(str + i, *(str + i)) == -1)
				not_paired(&str, &i);
			else
				i += find_pair(str + i, *(str + i));
		}
	}
	adding_new_tokens_to_list(command_table, str);
	free(str);
}

int	syntax_check(t_token *ct)
{
	t_token	*tmp;
	int		p_count;
	int		t_check1;

	tmp = ct;
	p_count = 0;
	while (tmp)
	{
		t_check1 = ft_token_checker(tmp, &p_count);
		if (t_check1 == 0)
			continue ;
		if (t_check1 != -5)
			return (t_check1);
		if (tmp->type == TOKEN_STR)
			string_completer(tmp);
		if (!tmp->next && p_count > 0)
			get_next_token(tmp);
		tmp = tmp->next;
	}
	return (0);
}
