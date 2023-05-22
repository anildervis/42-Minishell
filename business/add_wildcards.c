#include "../minishell.h"

int	add_double_quote(char **str, char *val)
{
	int	i;
	int	count;

	i = 1;
	count = find_pair(val, *DOUBLE_QUOTE);
	while (i < count)
	{
		if (*(val + i) == *DOLLAR_SIGN)
			i += add_dollar(str, (val + i));
		else
			i += add_char(str, (val + i));
	}
	return (i + 1);
}

int	add_single_quote(char **str, char *val)
{
	int	count;

	count = find_pair(val, *SINGLE_QUOTE);
	*str = ft_strjoin_freed(*str, ft_substr(val, 1, count - 1), 0b11);
	return (count + 1);
}

int	add_dollar(char **str, char *val)
{
	int	i;

	i = 2;
	if (*(val + 1) == *DOLLAR_SIGN)
		*str = ft_strjoin_freed(*str, ft_itoa(g_ms.parent_pid), 0b11);
	else if (*(val + 1) == *QUESTION_MARK)
		*str = ft_strjoin_freed(*str, ft_itoa(errno), 0b11);
	else if (*(val + 1) == *DOUBLE_QUOTE || *(val + 1) == *SINGLE_QUOTE)
		i -= add_char(str, DOLLAR_SIGN);
	else if (!(*(val + 1)) || *(val + 1) == ' ' || *(val + 1) == '\t' || *(val
			+ 1) == '\n')
		i -= add_char(str, DOLLAR_SIGN);
	else if (*(val + 1) == BRACETS[0])
	{
		i = find_pair(val, BRACETS[1]) + 1;
		*str = ft_strjoin_freed(*str, get_env(ft_substr(val, 2, i - 3)), 0b11);
	}
	else
		add_dollar_other(str, val);
	return (i);
}

void	add_dollar_other(char **str, char *val)
{
	int	i;

	i = 1;
	while (*(val + i) != ' ' && *(val + i) && *(val + i) != *DOUBLE_QUOTE
		&& *(val + i) != *SINGLE_QUOTE && *(val + i) != *DOLLAR_SIGN
		&& *(val + i) != *SLASH)
			i++;
	str = ft_strjoin_freed(str, get_env(ft_substr(val, 1, i - 1)), 0b11);
}
