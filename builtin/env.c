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
	if (!is_parent())
		exit(0);
}
