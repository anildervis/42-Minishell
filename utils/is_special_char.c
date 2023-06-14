#include "../minishell.h"

int is_special_char(char c)
{
    if ((c >= 42 && c <= 47) || (c <= 59 && c >= 58) || (c <= 64 && c >= 63) ||
        (c == '[') || (c == ']') || (c == '^') || (c == '{') || (c == '}') || (c == '~') ||
        (c == '#') || (c == '%'))
        return (1);
    return (0);
}