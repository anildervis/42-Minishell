#include "../minishell.h"

int is_metacharacter(char c)
{
    if (ft_strchr("|&><()", c))
        return 0;
    return 1;
}
