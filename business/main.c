/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:11:29 by binurtas          #+#    #+#             */
/*   Updated: 2023/05/20 15:26:07 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ms	g_ms;

void	init_ms(char **ev)
{
	errno = 0;
	g_ms.parent_pid = getpid();
	g_ms.child_pids = (int *)malloc(sizeof(int) * 100);
	g_ms.child_pids_count = 0;
	g_ms.opening_prompt = 0;
	g_ms.in_file = STDIN_FILENO;
	g_ms.out_file = STDOUT_FILENO;
	g_ms.ev = set_ev(ev);
	g_ms.paths = ft_split(getenv("PATH"), ':'); //Kontrol et
}

void	init_shell(char *str)
{
	t_token		*test;
	t_parsed	**parsed_commands;

	test = tokenizer(str);
	if (syntax_check(test))
		return ;
	parsed_commands = parse_commands(0, 1, test);
	executor(parsed_commands);
}

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

char	*display_prompt(void)
{
	char	*str;

	if (!g_ms.opening_prompt)
	{
		printf("\033[33m\033[1m\n \
 /$$      /$$ /$$           /$$           /$$                 /$$ /$$\n \
| $$$    /$$$|__/          |__/          | $$                | $$| $$\n \
| $$$$  /$$$$ /$$ /$$$$$$$  /$$  /$$$$$$$| $$$$$$$   /$$$$$$ | $$| $$\n \
| $$ $$/$$ $$| $$| $$__  $$| $$ /$$_____/| $$__  $$ /$$__  $$| $$| $$\n \
| $$  $$$| $$| $$| $$  \\ $$| $$|  $$$$$$ | $$  \\ $$| $$$$$$$$| $$| $$\n \
| $$\\  $ | $$| $$| $$  | $$| $$ \\____  $$| $$  | $$| $$_____/| $$| $$\n \
| $$ \\/  | $$| $$| $$  | $$| $$ /$$$$$$$/| $$  | $$|  $$$$$$$| $$| $$\n \
|__/     |__/|__/|__/  |__/|__/|_______/ |__/  |__/ \\_______/|__/|__/\n\n");
		g_ms.opening_prompt = 1;
	}
	if (!ft_strcmp(get_env("USER"), "aderviso") || !ft_strcmp(get_env("USER"),
			"anilalis"))
		str = ft_strjoin("\033[1m\033[31m", get_env("USER"));
	else if (!ft_strcmp(get_env("USER"), "bilalnrts")
		|| !ft_strcmp(get_env("USER"), "binurtas"))
		str = ft_strjoin("\033[1m\033[32m", get_env("USER"));
	else
		str = ft_strjoin("\033[1m\033[33m", get_env("USER"));
	str = ft_strjoin(str, "\033[34m ");
	return (ft_strjoin(str, ft_strjoin(getcwd(0, 0),
		" \033[31m︻\033[0m\033[32m┳\033[0m\033[33mデ\033[0m\033[34m═\033[0m\033[35m—\033[0m$ ")));
}

int	main(int ac, char **av, char **ev)
{
	char	*str;

	init_ms(ev);
	while (ac && av)
	{
		g_ms.ignore = 0;
		signal(SIGINT, &ctrl_c);
		signal(SIGQUIT, SIG_IGN);
		str = readline(display_prompt());
		ctrl_d(str);
		if (g_ms.ignore)
		{
			free(str);
			str = malloc(1);
		}
		if (*str)
		{
			init_shell(str);
			add_history(str);
			printf("\n");
		}
		free(str);
	}
	return (0);
}
