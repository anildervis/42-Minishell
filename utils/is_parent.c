#include "../minishell.h"

int	is_parent(void)
{
	return (g_ms.parent_pid == getpid());
}
