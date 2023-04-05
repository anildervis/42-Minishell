#include "../minishell.h"

void	builtin_env(void)
{
	char	**env;

	env = g_ms.ev;
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	if (g_ms.parent_pid != getpid())
		exit(0);
}
