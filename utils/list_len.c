#include "../minishell.h"

int	list_len(char **char_list)
{
	int	i;

	i = 0;
	while (char_list && char_list[i])
		i++;
	return (i);
}