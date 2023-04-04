#include "../minishell.h"

void close_fd(t_parsed *command, int default_in_file, int default_out_file)
{
    if (command->in_file != default_in_file)
        close(command->in_file);
    if (command->out_file != default_out_file)
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
        tmp = input;
        input = ft_strjoin(input, "\n");
        free(tmp);
        tmp = final_line;
        final_line = ft_strjoin(final_line, input);
        free(tmp);
        free(input);
        input = readline(">");
    }
    free(input);
    free(limiter);
    if (pipe(fd) == -1)
        ; // error
    write(fd[WRITE_END], final_line, ft_strlen(final_line));
    free(final_line);
    close(fd[WRITE_END]);
    return (fd[READ_END]);
}

int read_file_fd(char *file_name, int type)
{
    if (type == TOKEN_HERE_DOC)
        return (here_doc_fd(file_name));
    if (access(file_name, F_OK) == -1)
        ; // error
    if (access(file_name, R_OK) == -1)
        ; // permission error
    return (open(file_name, O_RDONLY, 0666));
}

int write_file_fd(char *file_name, int type)
{
    if (type == TOKEN_GREATER)
        return (open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0666));
    else if (type == TOKEN_APPEND)
        return (open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0666));
    return -1;
}

void apply_redirection(t_parsed **command, int default_in_file, int default_out_file)
{
    t_file *file_list;

    file_list = (*command)->file_list;
    if (!file_list)
        return ;
    while (file_list)
    {
        close_fd(*command, default_in_file, default_out_file);
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

void child_organizer(t_parsed *command, int default_in_file, int default_out_file)
{
    pid_t pid;

    (void)default_in_file;              //Kullanılmadığı için hata veriyor*************
    (void)default_out_file;             //Kullanılmadığı için hata veriyor*************
    pid = fork();
    if (pid < 0)
        ; // error
    else if (!pid)
    {
        organizer(command->parantheses_andor, command->in_file, command->out_file);
        exit(0);
    }
    waitpid(pid, &(g_ms.error_status), 0);
}

void command_executor(t_parsed *command, int default_in_file, int default_out_file)
{
    pid_t pid;

    expander(&command);
    pid = fork();
    if (pid < 0)
        ; // error
    else if (!pid)
    {
        dup2(command->in_file, STDIN_FILENO);
        dup2(command->out_file, STDOUT_FILENO);
        if (is_builtin(command->cmd))
            run_builtin(command->arguments);
        else
            execve(get_path(command->cmd), command->arguments, g_ms.ev);
    }
    waitpid(pid, &(g_ms.error_status), 0);
    close_fd(command, default_in_file, default_out_file);
}

void create_pipe(t_parsed **command, int default_in_file, int default_out_file)
{
    int fd[2];

    if (pipe(fd) == -1)
        ; // error
    if ((*command)->out_file != default_out_file)
        close((*command)->out_file);
    (*command)->out_file = fd[WRITE_END];
    if ((*command)->next->in_file != default_in_file)
        close((*command)->next->in_file);
    (*command)->next->in_file = fd[READ_END];
}

void create_redirections(t_parsed **andor_table, int default_in_file, int default_out_file)
{
    int i;
    t_parsed *tmp_command;

    i = -1;
    while (andor_table[++i])
    {
        tmp_command = andor_table[i];
        while (tmp_command)
        {
            if (tmp_command->next)
                create_pipe(&tmp_command, default_in_file, default_out_file);
            apply_redirection(&tmp_command, default_in_file, default_out_file);
            if (tmp_command->paranthesis)
            {
                tmp_command->parantheses_andor = parse_commands(tmp_command->in_file, tmp_command->out_file, tmp_command->paranthesis);
                create_redirections(tmp_command->parantheses_andor, default_in_file, default_out_file);
            }
            tmp_command = tmp_command->next;
        }
    }
}

void organizer(t_parsed **andor_table, int default_in_file, int default_out_file)
{
    int i;
    t_parsed *tmp_command;

    i = -1;
    while (andor_table[++i])
    {
        tmp_command = andor_table[i];
        if (tmp_command->exec == 3
            || (tmp_command->exec == TOKEN_AND && g_ms.error_status == 0)
            || (tmp_command->exec == TOKEN_OR && g_ms.error_status != 0))
            while (tmp_command)
            {
                if (tmp_command->paranthesis)
                    child_organizer(tmp_command, default_in_file, default_out_file);
                else
                    command_executor(tmp_command, default_in_file, default_out_file);
                tmp_command = tmp_command->next;
            }
    }
}

void executor(t_parsed **andor_table, int default_in_file, int default_out_file)
{
    create_redirections(andor_table, default_in_file, default_out_file);
    organizer(andor_table, default_in_file, default_out_file);
}
