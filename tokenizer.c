#include "minishell.h"

int is_token(char token)
{
    if (token == '|' || token == '&'
        || token == '>' || token == '<')
        return (1);
    return (0);
}

int add_token(char *input, t_token *command_table, enum tokens type, int len)
{
    int i;

    i = -1;
    if (len == 0)
        while (!is_token(*(input + ++i)))
            len++;
    if (command_table->prev == NULL)
}

t_token **find_token(char *input, t_token **command_table)
{
    while (1) // look for characters (*(input), " \n\t\0")
    {
        if (*(input) == '|')
            if (*(input + 1) == '|')
                input += add_token(input, command_table, TOKEN_OR, 2);
            else
                input += add_token(input, command_table, TOKEN_PIPE, 1);
        else if (*(input) == '&')
            if (*(input + 1) == '&')
                input += add_token(input, command_table, TOKEN_AND, 2);
            else
                input += add_token(input, command_table, TOKEN_APH, 1);
        else if (*(input) == '>')
            if (*(input + 1) == '>')
                input += add_token(input, command_table, TOKEN_APPEND, 2);
            else
                input += add_token(input, command_table, TOKEN_GREATER, 1);
        else if (*(input) == '<')
            if (*(input + 1) == '<')
                input += add_token(input, command_table, TOKEN_HERE_DOC, 2);
            else
                input += add_token(input, command_table, TOKEN_SMALLER, 1);
        else
            input += add_token(input, command_table, TOKEN_STR, 0);
    }
}

t_token **expand_wildcard(t_token **command_table);

t_token *tokenizer(char *input)
{
    t_token **command_table;


}

