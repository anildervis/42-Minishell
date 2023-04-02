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
	test = expander(test);
	parsed_commands = parse_commands(0, 1, test);
    organizer(parsed_commands, 0, 1);
}

int	main(int ac, char **av, char **ev)
{
	char	*str;

	init_ms(ev);
	while (1)
	{
		str = readline("\033[31m︻\033[0m\033[32m┳\033[0m\033[33mデ\033[0m\033[34m═\033[0m\033[35m—\033[0m$ ");
		if (*str)
		{
			init_shell(str);
			add_history(str);
		}
		if (str[0] == 'q')
		{
			break;
		}
	}
	return (0);
}
