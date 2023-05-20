/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:12:57 by binurtas          #+#    #+#             */
/*   Updated: 2023/05/20 14:12:58 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	size;

	str = (char *)malloc(len + 1);
	if (!s || !str)
		return (0);
	size = len;
	if (len > ft_strlen(s) && start < ft_strlen(s))
		size = ft_strlen(s) - start;
	if (start > ft_strlen(s))
	{
		str = (char *)malloc(1);
		if (!str)
			return (0);
		str[0] = '\0';
		return (str);
	}
	ft_strlcpy(str, s + start, size + 1);
	return (str);
}
