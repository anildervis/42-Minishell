#include "../minishell.h"

int is_metacharacter(char c)
{
    if (ft_strchr("|&><()", c))
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
    t_token *token;
    t_token *tmp_table;

    if (type == TOKEN_STR)
        len = token_str_lexer(input);
    token = (t_token *)malloc(sizeof(t_token));
    token->type = type;
    token->value = ft_substr(input, 0, len);
    token->next = NULL;
    token->prev = NULL;
    tmp_table = command_table;
    if (!(command_table->value))
    {
        command_table->value = ft_substr(input, 0, len);
        command_table->next = NULL;
        command_table->prev = NULL;
        command_table->type = type;
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

int print_syntax_error(char *value)
{
    g_ms.error_status = 2;
    printf("bash: syntax error near unexpected token '%s'", value);
    return (2);
}

void get_next_token(t_token *command_table)
{
    t_token *tmp_command_table;
    t_token *new_tokens;
    char *input;

    tmp_command_table = command_table;
    while (tmp_command_table->next)
        tmp_command_table = tmp_command_table->next;
    input = readline("> ");
    new_tokens = tokenizer(input);
    new_tokens->prev = tmp_command_table;
    tmp_command_table->next = new_tokens;
}

int syntax_check(t_token *command_table)
{
    t_token *tmp_command_table;
    int paranthesis_count;

    tmp_command_table = command_table;
    paranthesis_count = 0;
    while (tmp_command_table)
    {
        if (tmp_command_table->type == TOKEN_PIPE
            || tmp_command_table->type == TOKEN_AND
            || tmp_command_table->type == TOKEN_OR
            || tmp_command_table->type == TOKEN_CLOSE_PAR)
        {
            if (!tmp_command_table->prev
                || tmp_command_table->prev->type == TOKEN_OPEN_PAR
                || tmp_command_table->prev->type == TOKEN_PIPE
                || tmp_command_table->prev->type == TOKEN_AND
                || tmp_command_table->prev->type == TOKEN_OR)
                return (print_syntax_error(tmp_command_table->value));
            else if (tmp_command_table->type != TOKEN_CLOSE_PAR
                && !tmp_command_table->next)
            {
                get_next_token(tmp_command_table);
                break ;
            }
        }
        if (tmp_command_table->type == TOKEN_SMALLER
            || tmp_command_table->type == TOKEN_GREATER
            || tmp_command_table->type == TOKEN_HERE_DOC
            || tmp_command_table->type == TOKEN_APPEND)
        {
            if (!tmp_command_table->next)
                return (print_syntax_error("newline"));
            else if (tmp_command_table->next->type != TOKEN_STR)
                return (print_syntax_error(tmp_command_table->next->value));
        }
        else if (tmp_command_table->type == TOKEN_OPEN_PAR)
        {
            if (tmp_command_table->prev && tmp_command_table->prev->type == TOKEN_STR)
                return (print_syntax_error(tmp_command_table->value));
            paranthesis_count++;
        }
        else if (tmp_command_table->type == TOKEN_CLOSE_PAR)
        {
            if (tmp_command_table->next && tmp_command_table->next->type == TOKEN_STR)
                return (print_syntax_error(tmp_command_table->next->value));
            paranthesis_count--;
        }
        if (!tmp_command_table->next && paranthesis_count > 0)
        {
            get_next_token(tmp_command_table);
            break ;
        }
        tmp_command_table = tmp_command_table->next;
    }
    return (0);
}

// int main()
// {
//     t_token *test;
//     t_parsed **parsed_commands;
//     t_parsed *tmp_parsed;

//     // test = tokenizer("cat deneme.c | echo wow >xd.txt || echo \"'$HOME'\" && (ls <input.txt || echo wow | cat) >out.txt <<input.c >>output.c");
//     // test = tokenizer("echo uti*/ft_str*");
//     // test = tokenizer(" cat    \"ec\"'h'o \"$? $$\"");
//     test = tokenizer("ls >out.txt | (ls) <in.txt && ls");
//     // syntax_check(test); // last_exec_status = ;
//     test = expander(test);
//     parsed_commands = parse_commands(0, 1, test);
//     int i = -1;
//     while (parsed_commands[++i])
//     {
//         tmp_parsed = parsed_commands[i];
//         while (tmp_parsed)
//         {
//             printf("---------------------------\n");
//             printf("execution status -> %d\n", tmp_parsed->exec);
//             printf("infile -> %d\n", tmp_parsed->in_file);
//             printf("outfile -> %d\n", tmp_parsed->out_file);
//             printf("cmd -> %s\n", tmp_parsed->cmd);
//             int k = -1;
//             printf("arguments -> ");
//             while (tmp_parsed->arguments && tmp_parsed->arguments[++k])
//                 printf("%s, ", tmp_parsed->arguments[k]);
//             printf("\n");
//             k = 0;
//             printf("inside paranthesis -> ");
//             t_token *tmp = tmp_parsed->paranthesis;
//             while (tmp)
//             {
//                 printf("%s, ", tmp->value);
//                 tmp = tmp->next;
//             }
//             printf("\n");
//             t_file *tmp_file = tmp_parsed->file_list;
//             printf("redirections -> ");
//             while (tmp_file)
//             {
//                 printf("%d as %s, ", tmp_file->type, tmp_file->file_name);
//                 tmp_file = tmp_file->next;
//             }
//             printf("\n");
//             printf("---------------------------\n");
//             tmp_parsed = tmp_parsed->next;
//         }
//     }
//     organizer(parsed_commands, 0, 1);
// }
