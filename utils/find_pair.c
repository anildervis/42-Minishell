#include "../minishell.h"

/*
verilen inputun ilk karakterinin aynısını
kaç karakter sonrasında bulduğunu döndürüyor
*/
int	find_pair(char *input, char c)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = input;
	while (*(tmp + ++i))
	{
		if (*(tmp + i) == c)
			return (i);
	}
	return (-1);
}
