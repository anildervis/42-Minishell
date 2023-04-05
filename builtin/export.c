#include "../minishell.h"

int	env_len(void)
{
	int	i;

	i = -1;
	while (g_ms.ev[++i])
		;
	return (i);
}

int	check_env(char *str)
{
	char	*head;

	head = ft_strchr(str, '=');
	if (!head || (head == str))
		return (0);
	while (*str)
	{
		if (is_whitespace(*str))
			return (0);
		str++;
	}
	return (1);
}

void	add_env(char *str)
{
	int		i;
	char	**new_env;

	i = -1;
	new_env = ft_calloc(sizeof(char *), env_len() + 2);
	while (g_ms.ev[++i])
		new_env[i] = ft_strdup(g_ms.ev[i]);
	new_env[i] = ft_strdup(str);
	free_array(g_ms.ev);
	g_ms.ev = new_env;
}

int	is_include(char *str)
{
	int		i;
	int		j;

	i = 0;
	while (g_ms.ev[i])
	{
		j = 0;
		while (g_ms.ev[i][j] && str[j])
		{
			if (str[j] == '=' && g_ms.ev[i][j] == '=')
				return (i);
			if (str[j] != g_ms.ev[i][j])
				break ;
			j++;
		}
		i++;
	}
	return (-1);
}

void	builtin_export(char **input)
{
	int		pos;

	input++;
	while (*input)
	{
		if (check_env(*input))
		{
			pos = is_include(*input);
			if (pos != -1)
				g_ms.ev[pos] = ft_strdup(*input);
			else
				add_env(*input);
		}
		input++;
	}
	set_paths();
	if (g_ms.parent_pid != getpid())
		exit(1);
}
