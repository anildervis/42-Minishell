/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:11:37 by binurtas          #+#    #+#             */
/*   Updated: 2023/05/20 14:11:38 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_token_checker(t_token *tmp, int *p_count)
{
	int	t_check1;
	int	t_check2;

	t_check1 = ft_token_paoc(tmp);
	t_check2 = ft_token_sgha(tmp, p_count);
	if (t_check1 != 1 || t_check2 != 1)
	{
		free(p_count);
		if (t_check1 != 1)
			return (t_check1);
		return (t_check2);
	}
	return (-5);
}

int	ft_token_paoc(t_token *tmp)
{
	if (tmp->type == TOKEN_PIPE || tmp->type == TOKEN_AND
		|| tmp->type == TOKEN_OR || tmp->type == TOKEN_CLOSE_PAR)
	{
		if (!tmp->prev || tmp->prev->type == TOKEN_OPEN_PAR
			|| tmp->prev->type == TOKEN_PIPE || tmp->prev->type == TOKEN_AND
			|| tmp->prev->type == TOKEN_OR)
			return (print_error(SYNTAX_ERROR, tmp->value));
		else if (tmp->type != TOKEN_CLOSE_PAR && !tmp->next)
		{
			get_next_token(tmp);
			return (0);
		}
	}
	return (1);
}

int	ft_token_sgha(t_token *tmp, int *p_count)
{
	if (tmp->type == TOKEN_SMALLER || tmp->type == TOKEN_GREATER
		|| tmp->type == TOKEN_HERE_DOC || tmp->type == TOKEN_APPEND)
	{
		if (!tmp->next)
			return (print_error(SYNTAX_ERROR, "newline"));
		else if (tmp->next->type != TOKEN_STR)
			return (print_error(SYNTAX_ERROR, tmp->next->value));
	}
	else if (tmp->type == TOKEN_OPEN_PAR)
	{
		if (tmp->prev && tmp->prev->type == TOKEN_STR)
			return (print_error(SYNTAX_ERROR, tmp->value));
		*p_count += 1;
	}
	else if (tmp->type == TOKEN_CLOSE_PAR)
	{
		if (tmp->next && tmp->next->type == TOKEN_STR)
			return (print_error(SYNTAX_ERROR, tmp->next->value));
		*p_count -= 1;
	}
	return (1);
}
