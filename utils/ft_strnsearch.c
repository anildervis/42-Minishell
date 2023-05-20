/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnsearch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:12:53 by binurtas          #+#    #+#             */
/*   Updated: 2023/05/20 14:12:54 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strnsearch(char *string, char *chars_to_search, size_t len)
{
	int	i;
	int	k;

	k = -1;
	while (string[++k] && len-- > 0)
	{
		i = -1;
		while (chars_to_search[++i])
			if (chars_to_search[i] == string[k])
				return (0);
	}
	return (-1);
}
