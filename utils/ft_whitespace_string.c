/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_whitespace_string.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:53:03 by aderviso          #+#    #+#             */
/*   Updated: 2023/06/14 14:19:46 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_whitespace_string(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!is_whitespace(str[i]))
			return (-1);
	return (0);
}
