#include "minishell.h"

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
    //              BU KISIM İÇİN get_env FONKSİYONU LAZIM
    // else
    //     if (*(val + 1) == BRACETS[0])
    //     {
    //         i = find_pair(val, BRACETS[1]) + 1;
    //         ft_strjoin(str, get_env(ft_substr(val, 2, i - 3))); // get_env fonksiyonuna göre düzenlenecek
    //     }
    //     else
    //     {
    //         i = 1;
    //         while (*(val + i) != ' ' && *(val + i) && *(val + i) != *DOUBLE_QUOTE
	// 	        && *(val + i) != *SINGLE_QUOTE && *(val + i) != *DOLLAR_SIGN && *(val + i) != *SLASH)
    //             i++;
    //         ft_strjoin(str, get_env(ft_substr(val, 1, i - 1))); // get_env fonksiyonuna göre düzenlenecek
    //     }
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
    // printf("wild -> %s\n normal -> %s\n", wild_one, expected_one);
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
        tmp_wild_one = ft_strnstr(tmp_expected_one, tmp_wild_one, i);
        if (!tmp_wild_one)
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

void wildcard(char *path, char **destined_path, int way, t_token **command_table)
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
        // printf("%.1d/%.1d = %s\n", way, list_len(destined_path) - 1, ent->d_name);
        if (way != list_len(destined_path) - 1)
        {
            if (ent->d_type == DT_DIR && ft_strcmp(ent->d_name, ".") != 0 && ft_strcmp(ent->d_name, "..") != 0)
                if (wild_path(destined_path[way], ent->d_name))
                    wildcard(ft_strjoin(ft_strjoin(path, "/"), ent->d_name), destined_path, way + 1, command_table);
        }
        else
            if (ft_strcmp(ent->d_name, ".") != 0 && ft_strcmp(ent->d_name, "..") != 0)
                if (wild_path(destined_path[way], ent->d_name))
                    add_wildcard_to_list(ft_strjoin(ft_strjoin(path, "/"), ent->d_name), command_table);
    }
    closedir(dir);
}


void add_wildcard_to_list(char *path, t_token **command)
{
    t_token *token;

    token = (t_token *)malloc(sizeof(t_token));
    // printf("final_path %s\n", path);
    if (!ft_strnsearch((*command)->value, "*", ft_strlen((*command)->value)))
    {
        (*command)->value = path;
        free(token);
    }
    else
    {
        token->next = (*command)->next;
        token->prev = (*command);
        token->value = path;
        token->type = TOKEN_STR;
        (*command)->next = token;
        if (token->next)
            token->next->prev = token;
        (*command) = (*command)->next;
    }
}

void wildcard_expander(char *value, t_token **commands)
{
    int i;
    char **splitted_path;

    if (ft_strnsearch(value, "*", ft_strlen(value)))
        return ;
    i = -1;
    splitted_path = ft_split(value, '/');
    // printf("value -> %s\n", value);
    // i = -1;
    // while (splitted_path[++i])
    //     printf("path %d -> %s\n", i, splitted_path[i]);
    wildcard(".", splitted_path, 0, commands);
}


t_token *expander(t_token *command_list)
{
    t_token *expanded_list;

    expanded_list = command_list;
    while (expanded_list)
    {
        if (expanded_list->type == TOKEN_STR)
        {
            expanded_list->value = check_str(expanded_list->value);
            // printf("%d -> %s\n", 1, expanded_list->value);
            wildcard_expander(expanded_list->value, &expanded_list);
        }
        expanded_list = expanded_list->next;
    }
    // while (command_list)
    // {
    //     printf("%s\n", command_list->value);
    //     command_list = command_list->next;
    // }
    return command_list;
}
