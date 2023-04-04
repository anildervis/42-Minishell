/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:18:08 by aderviso          #+#    #+#             */
/*   Updated: 2023/04/02 11:47:17 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*strnstr_wildcard(const char *haystack, const char *needle, size_t len)
{
	size_t	index;
	size_t	k;
	char	*str;

	str = (char *)haystack;
	index = 0;
	if (!ft_strlen(needle))
		return (str);
	if (!len)
		return (0);
	while (str[index])
	{
		k = 0;
		while ((str[index + k] == needle[k]) && (k < len))
		{
			k++;
			if (!needle[k] || k == len)
				return (str + index);
		}
		index++;
	}
	return (0);
}
