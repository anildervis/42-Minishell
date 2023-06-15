/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:59:45 by aderviso          #+#    #+#             */
/*   Updated: 2023/06/15 18:45:20 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_d(char *str)
{
	if (!str)
	{
		printf("exit\n");
		exit(g_ms.error_no);
	}
}

void	ctrl_d_as_eof(char *str)
{
	if (!str)
		g_ms.ignore = 1;
}

void	ctrl_c(int sig)
{
	(void)sig;
	g_ms.ignore = 2;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	write(1, "\033[A", 3);
}

void	ctrl_c_inside_child(int sig)
{
	(void)sig;
	g_ms.error_no = 130;
}
