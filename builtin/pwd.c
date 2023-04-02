#include "../minishell.h"

void	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(0, 0);
	if (!cwd)
		perror("minishell ");
	else
		printf("%s\n", cwd);
	free(cwd);
	if (is_parent())
		exit(errno);
}
