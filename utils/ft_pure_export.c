#include "../minishell.h"

void	ft_pure_export()
{
	char	**export;
	char	*tmp;
	int		i;
	int		j;

	export = set_ev(g_ms.ev);
	i = 0;
	while (i < ft_size_aoa(export))
	{
		j = i + 1;
		while (j < ft_size_aoa(export))
		{
			if (ft_strcmp(export[i], export[j]) > 0)
			{
				tmp = export[i];
				export[i] = export[j];
				export[j] = tmp;
			}
			j++;
		}
		i++;
	}
    ft_pure_export_print(export);
}

void	ft_pure_export_print(char **export)
{
	int	i;

	i = -1;
	while (export[++i])
	{
		printf("declare -x ");
		printf("%s\n", export[i]);
	}
	free_array(export);
}