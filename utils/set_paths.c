#include "../minishell.h"

void	set_paths(void)
{
	char	*path;

	if (g_ms.paths)
		free_array(g_ms.paths);  // yapmasam leak mi oluşur ???
	path = get_env("PATH");
	if (!(*path))
		g_ms.paths = 0;
	else
		g_ms.paths = ft_split(path, ':');
	free(path);
}
