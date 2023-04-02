#include "../minishell.h"

/*
errno = 127 -> Command not found hatası
errno = 1 -> Operation not permitted hatası
*/

void	cmd_err(char *str)
{
	errno = 127;
	write(1, "minishell: ", 11);
	write(1, str, ft_strlen(str));
	write(1, ": command not found\n", 20);
	if (!is_parent())
		exit(errno);
}

void	no_file_err(char *str)
{
	if (ft_strchr(str, '/'))
		errno = 127;
	else
		errno = 1;
	write(1, "minishell: ", 11);
	write(1, str, ft_strlen(str));
	write(1, ": No such file or directory\n", 28);
	if (!is_parent())
		exit(errno);
}
