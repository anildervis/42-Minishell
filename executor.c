#include "minishell.h"

void close_fd(t_parsed *command)
{    
    if (command->in_file != STDIN_FILENO)
        close(command->in_file);
    if (command->out_file != STDOUT_FILENO)
        close(command->out_file);
}

int here_doc_fd(char *limiter)
{
    char *input;
    char *final_line;
    char *tmp;
    int fd[2];

    input = readline(">");
    final_line = (char *)ft_calloc(2, sizeof(char));
    while (ft_strcmp(limiter, input))
    {
        tmp = final_line;
        final_line = ft_strjoin(final_line, input);
        free(tmp);
        free(input);
        input = readline(">");
    }
    tmp = final_line;
    final_line = ft_strjoin(final_line, input);
    free(tmp);
    free(input);
    if (pipe(fd) == -1)
        // error
    write(fd[WRITE_END], final_line, ft_strlen(final_line));
    close(fd[WRITE_END]);
    return (fd[READ_END]);
}

int read_file_fd(char *file_name, int type)
{
    int fd;
    
    if (type == TOKEN_HERE_DOC)
        return (here_doc_fd(file_name));
    if (access(file_name, F_OK) == -1)
        // error
    if (access(file_name, R_OK) == -1)
        // permission error
    return (fd = open(file_name, O_RDONLY, 0666));
}

int write_file_fd(char *file_name, int type)
{
    int fd;

    if (type == TOKEN_GREATER)
        return (fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0666));
    if (type == TOKEN_APPEND)
        return (fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0666));
    return -1;
}

void apply_redirection(t_parsed **command)
{
    t_file *file_list;

    file_list = (*command)->file_list;
    if (!file_list)
        return ;
    while (file_list)
    {
        close_fd(*command);
        if (file_list->type == TOKEN_SMALLER)
            (*command)->in_file = read_file_fd(file_list->file_name, file_list->type);
        else if (file_list->type == TOKEN_HERE_DOC)
            (*command)->in_file = read_file_fd(file_list->file_name, file_list->type);
        else if (file_list->type == TOKEN_GREATER)
            (*command)->out_file = write_file_fd(file_list->file_name, file_list->type);
        else if (file_list->type == TOKEN_APPEND)
            (*command)->out_file = write_file_fd(file_list->file_name, file_list->type);
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
    else if (!pid)
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
    else if (!pid)
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