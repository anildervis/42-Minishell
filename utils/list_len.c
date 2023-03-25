#include "libft.h"

int	list_len(char **char_list)
{
	size_t	i;

	i = 0;
	while (char_list[i])
		i++;
	return (i);
}