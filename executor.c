#include "minishell.h"

void apply_redirection(t_parsed **command)
{
    t_file *file_list;

    file_list = (*command)->file_list;
    if (!file_list)
        return ;
    while (file_list)
    {
        if (file_list->type == TOKEN_SMALLER)
        else if (file_list->type == TOKEN_HERE_DOC)
        else if (file_list->type == TOKEN_GREATER)
        else if (file_list->type == TOKEN_APPEND)
        file_list = file_list->next;
    }
}

void child_organizer(t_parsed *command)
{
    t_token *inside_paranthesis;
    t_parsed *parsed_paranthesis;
    pid_t pid;

    inside_paranthesis = command->paranthesis;
    inside_paranthesis = expander(inside_paranthesis);
    parsed_paranthesis = parse_commands(command->in_file, command->out_file, inside_paranthesis);
    pid = fork();
    if (pid < 0)
        // error
    else if (pid == 0)
    {
        organizer(parsed_paranthesis);
        exit(1);
    }
    else
        waitpid(pid, NULL, NULL); // it will be -> waitpid(pid, &last_exec_status, NULL);
}

void command_executor(t_parsed *command)
{
    // there will be dup2
    pid_t pid;

    if (pid < 0)
        // error
    else if (pid == 0)
    {
        execve(command->cmd, command->arguments, NULL); //last will be environment variables
        exit(1);
    }
    else
        waitpid(pid, NULL, NULL); // it will be -> waitpid(pid, &last_exec_status, NULL);    
}

void organizer(t_parsed **andor_table)
{
    int i;
    t_parsed *tmp_command;

    i = -1;
    while (andor_table[++i])
    {
        tmp_command = andor_table[i];
        if (tmp_command->exec == 3
            || (tmp_command->exec == TOKEN_AND /*&& last_exec_status == 0*/)
            || (tmp_command->exec == TOKEN_OR /*&& last_exec_status != 0*/))
        while (tmp_command)
        {
            if (tmp_command->next)
                create_pipe(&tmp_command);
            apply_redirection(&tmp_command);
            if (tmp_command->paranthesis)
                child_organizer(tmp_command);
            else
                command_executor(tmp_command);
            tmp_command = tmp_command->next;
        }
    }
}