#include "../minishell.h"

void	add_dollar_other(char **str, char *val)
{
	int	i;

	i = 1;
	while (*(val + i) != ' ' && *(val + i) && *(val + i) != *DOUBLE_QUOTE
			&& *(val + i) != *SINGLE_QUOTE && *(val + i) != *DOLLAR_SIGN
			&& *(val + i) != *SLASH)
			i++;
	*str = ft_strjoin(*str, get_env(ft_substr(val, 1, i - 1)));
}

int	wild_path_helper(int star_count, char **tmp_wild_one, char **tmp_expected_one)
{
	int	i;

	while (star_count-- - 1 > 0)
	{
		i = 0;
		while (*tmp_wild_one[i] != *WILD_CARD)
			i++;
		*tmp_expected_one = strnstr_wildcard(*tmp_expected_one, *tmp_wild_one, i);
		if (!(*tmp_expected_one))
			return (0);
		*tmp_wild_one += i + 1;
		*tmp_expected_one += i;
	}
	return (1);
}
