/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:58:55 by aderviso          #+#    #+#             */
/*   Updated: 2022/10/22 14:48:16 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*a;
	size_t	i;

	i = 0;
	a = 0;
	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	a = (void *) malloc(size * count);
	if (!a)
		return (0);
	ft_bzero(a, size * count);
	return (a);
}
