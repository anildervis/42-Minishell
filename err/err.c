#include "../minishell.h"

/*
errno = 127 -> Command not found hatası
errno = 1 -> Operation not permitted hatası
*/

// void	cmd_err(char *str)
// {
// 	errno = 127;
// 	write(1, "minishell: ", 11);
// 	write(1, str, ft_strlen(str));
// 	write(1, ": command not found\n", 20);
// 	if (!is_parent())
// 		exit(errno);
// }

// void	no_file_err(char *str)
// {
// 	if (ft_strchr(str, '/'))
// 		errno = 127;
// 	else
// 		errno = 1;
// 	write(1, "minishell: ", 11);
// 	write(1, str, ft_strlen(str));
// 	write(1, ": No such file or directory\n", 28);
// 	if (!is_parent())
// 		exit(errno);
// }


// needs to be change by ft_putchar to write into stderror
int print_error(int error_code, char *param)
{
	errno = error_code;
	if (errno == FILE_NOT_FOUND)
		printf("minishell: %s: No such file or directory\n", param);
	else if (errno == SYNTAX_ERROR)
	    printf("bash: syntax error near unexpected token '%s'", param);
	else if (errno == CMD_NOT_FOUND)
		printf("minishell: %s: command not found\n", param);
	else if (errno == PERM_DENIED)
		printf("permission denied on %s\n", param);
	else if (errno == SYSTEM_ERR)
		printf("internal code error\n");
	else if (errno == MEMORY_ERR)
		printf("memory allocation failed\n");
	else if (errno == DUP_ERR)
		printf("could not duplicate fd\n");
	else if (errno == FORK_ERR)
		printf("could not create fork\n");
	else if (errno == PIPE_ERR)
		printf("could not create pipe\n");
	if (!is_parent())
		exit(errno);
	// free minishell ?
	return (errno);
}