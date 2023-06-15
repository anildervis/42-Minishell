#include "../minishell.h"

void	add_env(char *input)
{
	int		i;
	char	**new_env;

	i = -1;
	new_env = ft_calloc(sizeof(char *), ft_get_arg_count(g_ms.ev) + 2);
	while (g_ms.ev[++i])
		new_env[i] = ft_strdup(g_ms.ev[i]);
	new_env[i] = ft_strdup(input);
	free_array(g_ms.ev);
	g_ms.ev = new_env;
}

void	add_export(char *input)
{
	char	**new_export;
	int		i;

	i = -1;
	new_export = ft_calloc(sizeof(char *), ft_get_arg_count(g_ms.export) + 2);
	while (g_ms.export[++i])
		new_export[i] = ft_strdup(g_ms.export[i]);
	new_export[i] = ft_strdup(input);
	free_array(g_ms.export);
	g_ms.export = new_export;
	ft_sort_export();
}

void	ft_update_export(int index, char *input)
{
	free(g_ms.export[index]);
	g_ms.export[index] = ft_strdup(input);
}

void	ft_update_env(int index, char *input)
{
	free(g_ms.ev[index]);
	g_ms.ev[index] = ft_strdup(input);
}

void	ft_sort_export(void)
{
	char	*tmp;
	int		i;
	int		j;
	int		size;

	i = 0;
	size = ft_get_arg_count(g_ms.export);
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(g_ms.export[i], g_ms.export[j]) > 0)
			{
				tmp = g_ms.export[i];
				g_ms.export[i] = g_ms.export[j];
				g_ms.export[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
