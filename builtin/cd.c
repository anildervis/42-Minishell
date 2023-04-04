#include "../minishell.h"

void	builtin_cd(char **execute)
{
	if (execute[1])
	{
		if (chdir(execute[1]))
			perror("minishell ");
	}
	else
		if (chdir(getenv("HOME")))
			perror("minishell ");
	if (!is_parent())
		exit(errno);
}
