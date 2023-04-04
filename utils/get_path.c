#include "../minishell.h"

void	check_dir(char *cmd)
{
	DIR *dir;

	if (!cmd)
		exit(0);
	dir = opendir(cmd);
	if (dir && readdir(dir))
	{
		closedir(dir);
		exit(1);
	}
}

char	*free_new_path(char *np, char *path) // bu fonksiyon gereksiz ama diğer türlü 25 satırı geçiyor get_path xd
{
	free (np);
	return (path);
}

/*
Eğer path tamsa (var olan bir dosya yolunu yollarsan) 'minishell/builtin/cd' şeklinde bir path yollarsan bu pathi sana geri döndürür.
Eğer 'ls' şeklinde bir komut yollarsan pathlerin arasında arar ve cevap bulursa onu döndürür.
*/

char	*get_path(char *cmd)
{
	char	*path;
	char	**paths;
	char	*new_cmd;

	check_dir(cmd);
	if (!access(cmd, F_OK))
		return (ft_strdup(cmd));
	paths = g_ms.paths;
	// if (!paths)
	// 	command_err(cmd);
	new_cmd = ft_strjoin("/", cmd);
	while (*paths)
	{
		path = ft_strjoin(*paths, new_cmd);
		if (!access(path, F_OK))
			return (free_new_path(new_cmd, path));
		free(path);
		paths++;
	}
	if (ft_strchr(cmd, '/'))
		print_error(FILE_NOT_FOUND, cmd);
	free(new_cmd);
	return (0);
}
