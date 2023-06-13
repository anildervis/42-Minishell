/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:59:45 by aderviso          #+#    #+#             */
/*   Updated: 2023/06/13 15:00:37 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_c(int sig)
{
	(void)sig;
	g_ms.ignore = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	write(1, "\033[A", 3);
}

void	ctrl_d(char *str)
{
	if (!str)
	{
		printf("exit\n");
		exit(errno);
	}
}

void	ctrl_d_as_eof(char *str)
{
	if (!str)
		g_ms.ignore = 1;
}
