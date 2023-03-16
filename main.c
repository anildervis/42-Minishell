#include "minishell.h"

void	ft_set_path(t_ms *ms, char **ev)	// I know it is soooooo redundant...
{											// I will write this later.
	ms->path = ft_split(getenv("PATH"), ':');
}

void	ft_set_ev(t_ms *ms, char **ev)
{
	int	i;

	i = 0;
	while (ev[i])
		i++;
	ms->ev = (char **)malloc(sizeof(char *) * (i + 1));
	if (!ms->ev)
		return ;
	i = -1;
	while (ev[++i])
		ms->ev[i] = ft_strdup(ev[i]);
}


void	ft_init_ms(t_ms *ms, char **ev)
{
	ft_set_ev(ms, ev);					// sets ms->ev (char **) ~ copies environment variables
	ft_set_path(ms, ev);				// sets ms->path (char **) ~
}


int	main(int ac, char **av, char **ev)
{
	t_ms	ms;
	char	*str;

	ft_init_ms(&ms, ev);

	while (1)
	{
		str = readline("minishel>>>");
		if (str[0] == 'q')
			break;
	}
	return (0);
}
