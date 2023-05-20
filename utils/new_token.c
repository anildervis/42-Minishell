/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:13:16 by binurtas          #+#    #+#             */
/*   Updated: 2023/05/20 18:44:02 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*new_token(enum e_tokens type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->type = type;
	token->value = value;
	token->next = 0;
	token->prev = 0;
	return (token);
}
