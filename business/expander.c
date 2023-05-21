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
	return i + 1;
}

int	add_single_quote(char **str, char *val)
{
	int	count;

	count = find_pair(val, *SINGLE_QUOTE);
	*str = ft_strjoin_freed(*str, ft_substr(val, 1, count - 1), 0b11);
	return count + 1;
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
	else if (!(*(val + 1)) || *(val + 1) == ' '
		|| *(val + 1) == '\t' || *(val + 1) == '\n')
		i -= add_char(str, DOLLAR_SIGN);
	else
		if (*(val + 1) == BRACETS[0])
		{
			i = find_pair(val, BRACETS[1]) + 1;
			*str = ft_strjoin_freed(*str, get_env(ft_substr(val, 2, i - 3)), 0b11);
		}
		else
		{
			i = 1;
			while (*(val + i) != ' ' && *(val + i) && *(val + i) != *DOUBLE_QUOTE
				&& *(val + i) != *SINGLE_QUOTE && *(val + i) != *DOLLAR_SIGN && *(val + i) != *SLASH)
				i++;
			*str = ft_strjoin_freed(*str, get_env(ft_substr(val, 1, i - 1)), 0b11);
		}
	return i;
}

int	add_char(char **str, char *val)
{
	*str = ft_strjoin_freed(*str, ft_substr(val, 0, 1), 0b11);
	return 1;
}

char	*check_str(char *value)
{
    int		i;
    char	*str;

	i = 0;
	str = ft_calloc(2, sizeof(char));
	while (*(value + i))
	{
		if (*(value + i) == *DOUBLE_QUOTE)
			i += add_double_quote(&str, (value + i));
		else if (*(value + i) == *SINGLE_QUOTE)
			i += add_single_quote(&str, (value + i));
		else if (*(value + i) == *DOLLAR_SIGN)
			i += add_dollar(&str, (value + i));
		else
			i += add_char(&str, (value + i));
	}
	return (str);
}

void	updating_argument_list(int argument_no, t_parsed **command, char **wildcard_list)
{
	int		index;
	char	**arguments;	

	arguments = ft_calloc(list_len((*command)->arguments) + list_len(wildcard_list) + 2, sizeof(char *));
	index = -1;
	while (++index < argument_no)
		arguments[index] = ft_strdup((*command)->arguments[index]);
	index--;
	while (++index < list_len(wildcard_list) + argument_no)
		arguments[index] = ft_strdup(wildcard_list[index - argument_no]);
	index--;
	while (++index < list_len((*command)->arguments) + list_len(wildcard_list))
		arguments[index] = ft_strdup((*command)->arguments[index - list_len(wildcard_list) + 1]);
	arguments[index] = NULL;
	free_array((*command)->arguments);
	(*command)->arguments = arguments;
}

void	expander(t_parsed **command)
{
	int		i;
	char	**wildcard_list;

	i = -1;
	if (!(*command)->arguments || !((*command)->arguments[0]))
		return ;
	while ((*command)->arguments[++i])
	{
		(*command)->arguments[i] = check_str((*command)->arguments[i]);
		if (!wildcard_count((*command)->arguments[i]))
			continue ;
		wildcard_list = ft_calloc(2, sizeof(char *));
		wildcard(".", ft_split((*command)->arguments[i], '/'), 0, &wildcard_list);
		updating_argument_list(i, command, wildcard_list);
		i += list_len(wildcard_list) - 1;
		free_array(wildcard_list);
	}
}
