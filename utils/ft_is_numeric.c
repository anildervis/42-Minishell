#include "../minishell.h"

int ft_is_numeric(char c)
{
    if (c <= '9' && c >= '0')
        return (1);
    return (0);
}