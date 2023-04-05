#include "../minishell.h"

void	remove_env(char *data)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = ft_calloc(sizeof(char *), env_len() + 1);
	while (g_ms.ev[i])
	{
		if (ft_strncmp(g_ms.ev[i], data, ft_strlen(data)))
		{
			new_env[j] = ft_strdup(g_ms.ev[i]);
			j++;
		}
		i++;
	}
	new_env[j] = 0;
	free_array(g_ms.ev);
	g_ms.ev = new_env;
}

void	builtin_unset(char **input)
{
	char	*data;

	input++;
	while (*input)
	{
		data = ft_strjoin(*input, "=");
		remove_env(data);
		input++;
	}
	free(data);
	set_paths();
	if (g_ms.parent_pid != getpid())
		exit(1);
}
