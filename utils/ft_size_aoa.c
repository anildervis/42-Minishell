#include "../minishell.h"

int ft_size_aoa(char **arr)
{
    int i;
    int size;

    i = -1;
    size = 0;
    while (arr[++i])
        size++;
    return (size);
}