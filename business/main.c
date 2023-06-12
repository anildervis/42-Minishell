/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:11:29 by binurtas          #+#    #+#             */
/*   Updated: 2023/06/12 17:43:45 by aderviso         ###   ########.fr       */
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
	g_ms.paths = ft_split(getenv("PATH"), ':');
}

void	init_shell(char *str)
{
	t_token		*tokens;
	t_parsed	**parsed_commands;

	tokens = tokenizer(str);
	if ((!tokens || !tokens->value) || syntax_check(tokens))
	{
		free_tokens(tokens);
		return ;
	}
	parsed_commands = parse_commands(0, 1, tokens);
	executor(parsed_commands);
	free_all(tokens, parsed_commands);
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

void	display_prompt_print(void)
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
}

char	*display_prompt(void)
{
	char	*str;
	char	*user;

	user = get_env("USER");
	if (!g_ms.opening_prompt)
	{
		display_prompt_print();
		g_ms.opening_prompt = 1;
	}
	if (!ft_strcmp(user, "aderviso") || !ft_strcmp(user, "anilalis"))
		str = ft_strjoin("\033[1m\033[31m", user);
	else if (!ft_strcmp(user, "bilalnrts") || !ft_strcmp(user, "binurtas"))
		str = ft_strjoin("\033[1m\033[32m", user);
	else
		str = ft_strjoin("\033[1m\033[33m", user);
	free(user);
	str = ft_strjoin_freed(str, "@\033[34m", 0b10);
	str = ft_strjoin_freed(str, getcwd(0, 0), 0b11);
	str = ft_strjoin_freed(str, "\033[0m$ ", 0b10);
	return (str);
}

int	main(int ac, char **av, char **ev)
{
	char	*str;
	char	*prompt;

	init_ms(ev);
	while (ac && av)
	{
		g_ms.ignore = 0;
		signal(SIGINT, &ctrl_c);
		signal(SIGQUIT, SIG_IGN);
		prompt = display_prompt();
		str = readline(prompt);
		free(prompt);
		ctrl_d(str);
		if (g_ms.ignore)
		{
			free(str);
			str = malloc(1);
		}
		else if (*str)
		{
			init_shell(str);
			add_history(str);
		}
	}
	return (0);
}
