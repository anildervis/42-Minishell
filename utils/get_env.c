#include "../minishell.h"

/*	Eğer (char *str) null girerse; fonksiyon 0 dönecek.
	Ya da (char *str) yanlış bir env ismiyse boş bir adres dönecek. */

char	*get_env(char *str)
{
	int		i;
	int		j;
	char	*strp;

	i = -1;
	j = 0;
	strp = ft_strjoin(str, "=");
	while (g_ms.ev[++i])
	{
		if (!ft_strncmp(g_ms.ev[i], strp, ft_strlen(strp)))
		{
			while (g_ms.ev[i][j] != '=')
				j++;
			return (ft_strdup(&g_ms.ev[i][j + 1]));
		}
	}
	return (ft_calloc(sizeof(char *), 1));
}
