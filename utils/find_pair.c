/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_pair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:12:23 by binurtas          #+#    #+#             */
/*   Updated: 2023/05/20 14:12:24 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
verilen inputun ilk karakterinin aynısını
kaç karakter sonrasında bulduğunu döndürüyor
*/
int	find_pair(char *input, char c)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = input;
	while (*(tmp + ++i))
	{
		if (*(tmp + i) == c)
			return (i);
	}
	return (-1);
}
