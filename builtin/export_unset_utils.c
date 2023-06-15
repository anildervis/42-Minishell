#include "../minishell.h"

int check_char(char *command, char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (is_special_char(input[i]) || ft_is_numeric(input[0]) || input[0] == '=')
		{
			errno = 1;
			printf("minishell: %s: %s: not a valid identifier\n", command, input);
			return (1);
		}
		i++;
	}
	return (0);
}

int ft_is_exist_export(char *input)
{
	int i;
	int j;

	i = -1;
	while (g_ms.export[++i])
	{
		j = 0;
		while (g_ms.export[i][j] && input[j])
		{
			if (input[j] == '=' && g_ms.export[i][j] == '=')
				return (i);
			if (input[j] != g_ms.export[i][j])
				break ;
			if (!input[j + 1] && !g_ms.export[i][j + 1] && input[j] == g_ms.export[i][j])
				return (i);
			j++;
		}
		if (!input[j] && g_ms.export[i][j] == '=')
			return (-2);
		if (!g_ms.export[i][j] && input[j] == '=' && g_ms.export[i][j - 1] == input[j - 1]) // export -> abc | input -> abc=
			return (i);
	}
	return (-1);
}

int ft_is_exist_env(char *input)
{
	int	i;
	int	j;

	i = -1;
	while (g_ms.ev[++i])
	{
		j = 0;
		while (g_ms.ev[i][j] && input[j])
		{
			if (input[j] == '=' && g_ms.ev[i][j] == '=')
				return (i);
			if (input[j] != g_ms.ev[i][j])
				break ;
			j++;
		}
	}
	return (-1);
}

int is_there_equal(char *input)
{
	char	*head;

	head = ft_strchr(input, '=');
	if (head && head != input)
		return (1);
	return (0);
}
