/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:18:08 by aderviso          #+#    #+#             */
/*   Updated: 2022/10/22 15:00:15 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		k;
	char	*str;

	str = (char *)haystack;
	i = 0;
	if (!ft_strlen(needle))
		return (str);
	if (!len)
		return (0);
	while ((str[i]) && (i < len))
	{
		k = 0;
		while ((str[i + k] == needle[k]) && ((i + k) < len))
		{
			k++;
			if (!needle[k])
				return (str + i);
		}
		i++;
	}
	return (0);
}
