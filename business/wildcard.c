#include "../minishell.h"

int	wildcard_count(char *wild_string)
{
	int	i;
	int	wildcard_count;

	i = 0;
	wildcard_count = 0;
	while (wild_string[i])
	{
		if (wild_string[i++] == *WILD_CARD)
			wildcard_count++;
	}
	return (wildcard_count);
}

// returns 0 if the strings doesn't match
int	checking_between_wildcards(int wildcard_count, char *wild_str,
		char *expected_str)
{
	int	i;

	while (wildcard_count-- - 1 > 0)
	{
		i = 0;
		while (wild_str[i] != *WILD_CARD)
			i++;
		expected_str = strnstr_wildcard(expected_str, wild_str, i);
		if (!expected_str)
			return (0);
		wild_str += i + 1;
		expected_str += i;
	}
	if (ft_strlen(expected_str) > ft_strlen(wild_str))
		expected_str += ft_strlen(expected_str) - ft_strlen(wild_str);
	return (!ft_strcmp(wild_str, expected_str));
	// comparing the part after the last wildcard
}

int	is_wild_eq_string(char *wild_str, char *expected_str)
{
	int	i;
	int	count;

	i = 0;
	count = wildcard_count(wild_str);
	if (!count) // getting wildcard count
		return (!ft_strcmp(wild_str, expected_str));
	i = 0;
	while (wild_str[i] && wild_str[i] != *WILD_CARD)
	// getting the index of first wildcard
		i++;
	if (i != 0 && ft_strncmp(wild_str, expected_str, i))
	// comparing the part before the first wildcard
		return (0);
	wild_str += i + 1;
	expected_str += i;
	if (!checking_between_wildcards(count, wild_str, expected_str))
	// checking if between the wildcards are correct
		return (0);
	return (1);
}

void	add_wildcard_to_list(char *path, char ***arguments)
{
	int		i;
	char	**new_list;

	new_list = ft_calloc(list_len(*arguments) + 2, sizeof(char *));
	i = -1;
	while ((*arguments)[++i])
		new_list[i] = ft_strdup((*arguments)[i]);
	new_list[i] = ft_strdup(path + 2);
	free_array(*arguments);
	free(path);
	*arguments = new_list;
}

void	wildcard(char *path, char **destined_path, int way, char ***arguments)
{
	DIR				*dir;
	struct dirent	*ent;

	dir = opendir(path);
	if (!dir)
		open_file_error();
	ent = readdir(dir);
	while (ent)
	{
		if (way != list_len(destined_path) - 1)
		{
			if (ent->d_type == DT_DIR && (ft_strncmp(ent->d_name, ".", 1)
					|| !ft_strncmp(ent->d_name, destined_path[way], 1)))
				if (is_wild_eq_string(destined_path[way], ent->d_name))
					wildcard(ft_strjoin(ft_strjoin(path, "/"), ent->d_name),
						destined_path, way + 1, arguments);
		}
		else if (ft_strncmp(ent->d_name, ".", 1) || !ft_strncmp(ent->d_name,
				destined_path[way], 1))
			if (is_wild_eq_string(destined_path[way], ent->d_name))
				add_wildcard_to_list(ft_strjoin_freed(ft_strjoin(path, "/"),
					ent->d_name, 0b10), arguments);
		ent = readdir(dir);
	}
	closedir(dir);
}
