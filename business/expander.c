#include "../minishell.h"

int add_double_quote(char **str, char *val)
{
    int i;
    int count;

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

int add_single_quote(char **str, char *val)
{
    int count;

    count = find_pair(val, *SINGLE_QUOTE);
    *str = ft_strjoin(*str, ft_substr(val, 1, count - 1));
    return count + 1;
}

int add_dollar(char **str, char *val)
{
    int i;

    i = 2;
    if (*(val + 1) == *DOLLAR_SIGN)
        *str = ft_strjoin(*str, "123"); // ft_itoa(t_ms->pid)); // global değişkenin pid'si
    else if (*(val + 1) == *QUESTION_MARK)
        *str = ft_strjoin(*str, "42"); // ft_itoa(t_ms->error_status)); // global değişkenin son komut çıktısı
    else if (*(val + 1) == *DOUBLE_QUOTE || *(val + 1) == *SINGLE_QUOTE)
        i -= add_char(str, DOLLAR_SIGN);
    else if (!(*(val + 1)) || *(val + 1) == ' '
        || *(val + 1) == '\t' || *(val + 1) == '\n')
        i -= add_char(str, DOLLAR_SIGN);
    else
        if (*(val + 1) == BRACETS[0])
        {
            i = find_pair(val, BRACETS[1]) + 1;
            *str = ft_strjoin(*str, get_env(ft_substr(val, 2, i - 3)));
        }
        else
        {
            i = 1;
            while (*(val + i) != ' ' && *(val + i) && *(val + i) != *DOUBLE_QUOTE
		        && *(val + i) != *SINGLE_QUOTE && *(val + i) != *DOLLAR_SIGN && *(val + i) != *SLASH)
                i++;
            *str = ft_strjoin(*str, get_env(ft_substr(val, 1, i - 1)));
        }
    return i;
}

int add_char(char **str, char *val)
{
    *str = ft_strjoin(*str, ft_substr(val, 0, 1));
    return 1;
}

char *check_str(char *value)
{
    int i;
    char *str;

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

int wild_path(char *wild_one, char *expected_one)
{
    int i;
    int star_count;
    char *tmp_wild_one;
    char *tmp_expected_one;
    tmp_wild_one = wild_one;
    tmp_expected_one = expected_one;
    i = 0;
    star_count = 0;
    while (tmp_wild_one[i])
        if (tmp_wild_one[i++] == *WILD_CARD)
            star_count++;
    if (!star_count)
        return !ft_strcmp(tmp_wild_one, tmp_expected_one);
    i = 0;
    while (tmp_wild_one[i] && tmp_wild_one[i] != *WILD_CARD)
        i++;
    if (i != 0)
        if (ft_strncmp(tmp_wild_one, tmp_expected_one, i))
            return 0;
    tmp_wild_one += i + 1;
    tmp_expected_one += i;
    while (star_count-- - 1 > 0)
    {
        i = 0;
        while (tmp_wild_one[i] != *WILD_CARD)
            i++;
        tmp_expected_one = strnstr_wildcard(tmp_expected_one, tmp_wild_one, i);
        if (!tmp_expected_one)
            return 0;
        tmp_wild_one += i + 1;
        tmp_expected_one += i;
    }
    if (ft_strlen(tmp_expected_one) < ft_strlen(tmp_wild_one))
        return -1;
    else
        tmp_expected_one += ft_strlen(tmp_expected_one) - ft_strlen(tmp_wild_one);
    return !ft_strcmp(tmp_wild_one, tmp_expected_one);
}

void    wildcard(char *path, char **destined_path, int way, char ***arguments)
{
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(path)) == NULL)
    {
        perror("Failed to open directory");
        exit(EXIT_FAILURE);
    }
    while ((ent = readdir(dir)) != NULL)
    {
        if (way != list_len(destined_path) - 1)
        {
            if (ent->d_type == DT_DIR && (ft_strncmp(ent->d_name, ".", 1) || !ft_strncmp(ent->d_name, destined_path[way], 1)))
                if (wild_path(destined_path[way], ent->d_name))
                    wildcard(ft_strjoin(ft_strjoin(path, "/"), ent->d_name), destined_path, way + 1, arguments);
        }
        else
            if (ft_strncmp(ent->d_name, ".", 1) || !ft_strncmp(ent->d_name, destined_path[way], 1))
                if (wild_path(destined_path[way], ent->d_name))
                    add_wildcard_to_list(ft_strjoin(ft_strjoin(path, "/"), ent->d_name), arguments);
    }
    closedir(dir);
}


void add_wildcard_to_list(char *path, char ***arguments)
{
    int     i;
    char    **new_list;

    new_list = ft_calloc(list_len(*arguments) + 2, sizeof(char *));
    i = -1;
    while ((*arguments)[++i])
        new_list[i] = ft_strdup((*arguments)[i]);
    new_list[i] = ft_strdup(path + 2);
    *arguments = new_list;
}

void	expander(t_parsed **command)
{
	int		i;
	int		k;
	char	*tmp_argument;
	char	**tmp_arguments;
	char	**wildcard_list;

    (void)tmp_argument;                 //Kullanılmadığı için hata veriyor****************
	i = -1;
	wildcard_list = ft_calloc(2, sizeof(char *));
	if (!(*command)->arguments || !((*command)->arguments[0]))
		return ;
	while ((*command)->arguments[++i])
	{
		(*command)->arguments[i] = check_str((*command)->arguments[i]);
		if (ft_strnsearch((*command)->arguments[i], "*", ft_strlen((*command)->arguments[i])))
			continue ;
		wildcard(".", ft_split((*command)->arguments[i], '/'), 0, &wildcard_list);
		tmp_arguments = ft_calloc(list_len((*command)->arguments) + list_len(wildcard_list), sizeof(char *));
		k = -1;
		while (++k < i)
			tmp_arguments[k] = ft_strdup((*command)->arguments[k]);
		i = -1;
		while (++i < list_len(wildcard_list))
			tmp_arguments[k + i] = ft_strdup(wildcard_list[i]);
		while (k < list_len((*command)->arguments))
        {
			tmp_arguments[k + i] = ft_strdup((*command)->arguments[k]);     //unsequenced modification and access to 'k'*************
            k++;                                                            //önceki hali(196. satır) : ft_strdup((*command)->arguments[k++]***
        }
		tmp_arguments[k + i] = NULL;
		(*command)->arguments = tmp_arguments;
		i += list_len(wildcard_list);
	}
}
