/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:11:16 by binurtas          #+#    #+#             */
/*   Updated: 2023/05/20 14:11:17 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_char(char **str, char *val)
{
	*str = ft_strjoin_freed(*str, ft_substr(val, 0, 1), 0b11);
	return (1);
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
	free(value);
	return (str);
}

void	updating_argument_list(int argument_no, t_parsed **command,
		char **wildcard_list)
{
	int		index;
	char	**arguments;

	arguments = ft_calloc(list_len((*command)->arguments)
			+ list_len(wildcard_list) + 2, sizeof(char *));
	index = -1;
	while (++index < argument_no)
		arguments[index] = ft_strdup((*command)->arguments[index]);
	index--;
	while (++index < list_len(wildcard_list) + argument_no)
		arguments[index] = ft_strdup(wildcard_list[index - argument_no]);
	index--;
	while (++index < list_len((*command)->arguments) + list_len(wildcard_list))
		arguments[index] = ft_strdup((*command)->arguments[index
				- list_len(wildcard_list) + 1]);
	arguments[index] = NULL;
	free_array((*command)->arguments);
	(*command)->arguments = arguments;
}

void	expander(t_parsed **command)
{
	int		i;
	char	*file;
	char	**given_path;
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
		given_path = ft_split((*command)->arguments[i], '/');
		file = ft_strdup(".");
		wildcard(file, given_path, 0, &wildcard_list);
		free_array(given_path);
		updating_argument_list(i, command, wildcard_list);
		i += list_len(wildcard_list) - 1;
		free_array(wildcard_list);
	}
}
