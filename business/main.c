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
    // t_parsed *tmp_parsed;

	test = tokenizer(str);
	if (syntax_check(test))
		return ;
	test = expander(test);
	parsed_commands = parse_commands(0, 1, test);
    // int i = -1;
    // while (parsed_commands[++i])
    // {
    //     tmp_parsed = parsed_commands[i];
    //     while (tmp_parsed)
    //     {
    //         printf("---------------------------\n");
    //         printf("execution status -> %d\n", tmp_parsed->exec);
    //         printf("infile -> %d\n", tmp_parsed->in_file);
    //         printf("outfile -> %d\n", tmp_parsed->out_file);
    //         printf("cmd -> %s\n", tmp_parsed->cmd);
    //         int k = -1;
    //         printf("arguments -> ");
    //         while (tmp_parsed->arguments && tmp_parsed->arguments[++k])
    //             printf("%s, ", tmp_parsed->arguments[k]);
    //         printf("\n");
    //         k = 0;
    //         printf("inside paranthesis -> ");
    //         t_token *tmp = tmp_parsed->paranthesis;
    //         while (tmp)
    //         {
    //             printf("%s, ", tmp->value);
    //             tmp = tmp->next;
    //         }
    //         printf("\n");
    //         t_file *tmp_file = tmp_parsed->file_list;
    //         printf("redirections -> ");
    //         while (tmp_file)
    //         {
    //             printf("%d as %s, ", tmp_file->type, tmp_file->file_name);
    //             tmp_file = tmp_file->next;
    //         }
    //         printf("\n");
    //         printf("---------------------------\n");
    //         tmp_parsed = tmp_parsed->next;
    //     }
    // }
    organizer(parsed_commands, 0, 1);
}

int	main(int ac, char **av, char **ev)
{
	char	*str;

	init_ms(ev);
	while (1)
	{
		str = readline(ft_strjoin(getcwd(0, 0), " \033[31m︻\033[0m\033[32m┳\033[0m\033[33mデ\033[0m\033[34m═\033[0m\033[35m—\033[0m$ "));
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
