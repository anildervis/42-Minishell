#include "minishell.h"

// There is a string search function better suited for the underlaying two functions

int is_metacharacter(char c)
{
    if (c == '|' || c == '&'
        || c == '>' || c == '<'
        || c == '(' || c == ')')
        return 1;
    return 0;
}

int token_str_lexer(char *input)
{
    int i;

    i = 0;
    while (*(input + i) && !is_metacharacter(*(input + i))
        && *(input + i) != ' '
        && *(input + i) != '\t'
        && *(input + i) != '\n')
    {
        if (*(input + i) == *DOUBLE_QUOTE)
            i += find_pair(input + i, *DOUBLE_QUOTE);
        else if (*(input + i) == *SINGLE_QUOTE)
            i += find_pair(input + i, *SINGLE_QUOTE);
        else
            i++;
    }
    return i;
}

int add_token(char *input, t_token **command_table, enum tokens type, int len)
{
    int i;
    t_token *token;
    t_token *tmp_table;

    i = -1;
    token = (t_token *)malloc(sizeof(t_token));
    token->type = type;
    if (type == TOKEN_STR)
        len = token_str_lexer(char *input);
    token->value = ft_substr(input, 0, len);
    token->next = NULL;
    tmp_table = command_table;
    if (!(*tmp_table))
    {
        tmp_table->prev = NULL;
        *tmp_table = token;
    }
    else
    {
        while (tmp_table->next)
            tmp_table = tmp_table->next;
        token->prev = tmp_table;
        tmp_table->next = token;
    }
    return len;
}

t_token **find_token(char *input, t_token **command_table)
{
    while (*(input))
    {
        if (*(input) == '&' && *(input + 1) == '&')
            input += add_token(input, command_table, TOKEN_AND, 2);
        else if (*(input) == '(')
            input += add_token(input, command_table, TOKEN_OPEN_PAR, 1);
        else if (*(input) == ')')
            input += add_token(input, command_table, TOKEN_CLOSE_PAR, 1);
        else if (*(input) == '|')
            if (*(input + 1) == '|')
                input += add_token(input, command_table, TOKEN_OR, 2);
            else
                input += add_token(input, command_table, TOKEN_PIPE, 1);
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
        else if (*(input) == ' ' || *(input) == '\t' || *(input) == '\n')
            input += 1;
        else
            input += add_token(input, command_table, TOKEN_STR, 0);
    }
}

t_token **tokenizer(char *input)
{
    t_token **command_table;

    // !!!!!!!!!!! mallocation needs correction !!!!!!!!!!!!!!!
    command_table = (t_token **)malloc((t_token *) * 10);
    command_table = NULL;


}

