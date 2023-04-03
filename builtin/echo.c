#include "../minishell.h"

void	put_char(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		write(1, &input[i], 1);
		i++;
	}
}

void	builtin_echo(char **input)
{
	int	i;

	i = 1;
	if (!ft_strcmp(input[1], "-n"))
		i = 2;
	while (input[i])
	{
		put_char(input[i]);
		if (input[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (ft_strcmp(input[1], "-n"))
		write(STDOUT_FILENO, "\n", 1);
	if (!is_parent())
		exit(0);
}
