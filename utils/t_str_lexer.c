#include "../minishell.h"

int token_str_lexer(char *input)
{
    int i;

    i = 0;
    while (*(input + i) && is_metacharacter(*(input + i))
        && ft_strnsearch((input + i), " \t\n", 1))
    {
        if (*(input + i) == *DOUBLE_QUOTE)
            i += find_pair(input + i, *DOUBLE_QUOTE) + 1;
        else if (*(input + i) == *SINGLE_QUOTE)
            i += find_pair(input + i, *SINGLE_QUOTE) + 1;
        else
            i++;
    }
    return i;
}
