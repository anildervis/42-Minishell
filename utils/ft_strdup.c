#include "../minishell.h"

char	*ft_strdup(const char *str)
{
	int		i;
	char	*s1;

	if (!str)
		return (0);
	i = 0;
	s1 = malloc(ft_strlen(str) + 1);
	if (!s1)
		return (0);
	while (str[i])
	{
		s1[i] = str[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
