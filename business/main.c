#include "../minishell.h"

t_ms	g_ms;

void	init_ms(char **ev)
{
	g_ms.parent_pid = getpid();
	g_ms.ev = set_ev(ev);
	g_ms.paths = ft_split(getenv("PATH"), ':');    //Kontrol et
}

void	init_shell(char *str)
{
    t_token *test;
    t_parsed **parsed_commands;

	test = tokenizer(str);
	if (syntax_check(test))
		return ;
	parsed_commands = parse_commands(0, 1, test);
    executor(parsed_commands, 0, 1);
}

void    ctrl_c(int sig)
{
    (void)sig;
    g_ms.ignore = 1;
    ioctl(STDIN_FILENO, TIOCSTI, "\n");
    write(1, "\033[A", 3);
}

void    ctrl_d(char *str)
{
    if (!str)
    {
        printf("exit\n");
        exit(errno);
    }
}

int	main(int ac, char **av, char **ev)
{
	char	*str;

	init_ms(ev);
	while (ac && av)
	{
        g_ms.ignore = 0;
        signal(SIGINT, &ctrl_c);
        signal(SIGQUIT, SIG_IGN);   // ctrl + \ sinyalini
		str = readline(ft_strjoin(getcwd(0, 0), " \033[31m︻\033[0m\033[32m┳\033[0m\033[33mデ\033[0m\033[34m═\033[0m\033[35m—\033[0m$ "));
		ctrl_d(str);                // bu sinyal 'end of file' karakteri. '\0'.
        if (g_ms.ignore)
        {
            free(str);
            str = malloc(1);
        }
        if (*str)
		{
			init_shell(str);
			add_history(str);
		}
        free(str);
	}
	return (0);
}
