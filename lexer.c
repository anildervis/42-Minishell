#include "minishell.h"

int is_metacharacter(char c)
{
    if (!ft_strnsearch(&c, "|&><()", 1))
        return 0;
    return 1;
}

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

int add_token(char *input, t_token *command_table, enum tokens type, int len)
{
    int i;
    t_token *token;
    t_token *tmp_table;

    i = -1;
    token = (t_token *)malloc(sizeof(t_token));
    token->type = type;
    if (type == TOKEN_STR)
        len = token_str_lexer(input);
    token->value = ft_substr(input, 0, len);
    printf("input -> %s for %d\n", token->value, len);
    token->next = NULL;
    token->prev = NULL;
    tmp_table = command_table;
    if (!tmp_table)
        tmp_table = token;
    else
    {
        while (tmp_table->next)
            tmp_table = tmp_table->next;
        token->prev = tmp_table;
        tmp_table->next = token;
    }
    return len;
}

void find_token(char *input, t_token *command_table)
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

t_token *tokenizer(char *input)
{
    t_token *command_table;

    command_table = (t_token *)ft_calloc(1, sizeof(t_token));
    find_token(input, command_table);
    return (command_table);
}

int main()
{
    t_token *test;
    
    test = tokenizer("echo uti*/ft_str*");
    //(" cat    \"ec\"'h'o \"$? $$\"");
    //("cat deneme.c && (ls <input.txt || echo wow | cat) >out.txt <<input.c >>output.c");
    test = expander(test);
}