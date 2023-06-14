/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:11:59 by binurtas          #+#    #+#             */
/*   Updated: 2023/06/12 20:50:26 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
***********BİTMEDİ***********
*/

int	env_len(void)
{
	int	i;

	i = -1;
	while (g_ms.ev[++i])
		;
	return (i);
}

int check_char(char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (is_special_char(input[i]) || ft_is_numeric(input[0]) || input[0] == '=')
		{
			errno = 1;
			printf("minishell: export: %s: not a valid identifier\n", input);
			return (1);
		}
		i++;
	}
	return (0);
}
//burak
//^
int is_there_equal(char *input)
{
	char    *head;

	head = ft_strchr(input, '=');
	printf("\nhead = %s\n", head);
	printf("\ninput = %s\n", input);
	if (head && head != input)
	{
		printf("Buraya girdi\n");
		return (1);
	}
	return (0);
}

/*
bilal
bila
bil
-> bil=
*/

int ft_is_exist_export(char *input)
{
	int i;
	int j;

	i = -1;
	while (g_ms.export[++i])
	{
		j = 0;
		while (g_ms.export[i][j] && input[j])
		{
			if (input[j] == '=' && g_ms.export[i][j] == '=')
				return (i);
			if (input[j] != g_ms.export[i][j])
				break ;
			j++;
		}
		if (!input[j] && g_ms.export[i][j] == '=')
			return (-2);
		if (!g_ms.export[i][j] && input[j] == '=' && g_ms.export[i][j - 1] == input[j - 1]) // export -> abc | input -> abc=
			return (i);
	}
	return (-1);
}

int ft_is_exist_env(char *input)
{
	int	i;
	int	j;

	i = -1;
	while (g_ms.ev[++i])
	{
		j = 0;
		while (g_ms.ev[i][j] && input[j])
		{
			if (input[j] == '=' && g_ms.ev[i][j] == '=')
				return (i);
			if (input[j] != g_ms.ev[i][j])
				break ;
			j++;
		}
	}
	return (-1);
}

void    new_builtin_export(char **input)
{
	int check_env;
	int check_export;
	int i;
	//export bilal=42 burak=talha talha
	printf("0 buradayim\n");
	if (!input[1])
		ft_pure_export_print();
	i = 1;
	while (input[i])
	{
		printf("1 buradayim\n");
		if (check_char(input[i]))
		{
			i++;
			continue ;
		}
		printf("2 buradayim\n");
		check_export = ft_is_exist_export(input[i]); // -1 -> yok else index döner
		check_env = ft_is_exist_env(input[i]);
		printf("\n\nenv_ciktisi = %d\n\n", check_env);
		printf("\n\nexport_ciktisi = %d\n\n", check_export);
		printf("3 buradayim\n");
		if (is_there_equal(input[i]))
		{
			printf("4 buradayim\n");
			if (check_export >= 0)
			{
				printf("4.1 buradayim\n");
				free(g_ms.export[check_export]);
				g_ms.export[check_export] = ft_strdup(input[i]);
			}
			else
			{
				printf("4.2 buradayim\n");
				add_export(input[i]);
			}
			if (check_env >= 0)
			{
				printf("4.3 buradayim\n");
				free(g_ms.ev[check_env]);
				g_ms.ev[check_env] = ft_strdup(input[i]);
			}
			else
			{
				printf("4.4 buradayim\n");
				add_env(input[i]);
			}
		}
		else
		{
			printf("6 buradayim\n");
			if (check_export >= 0)
			{
				printf("6.1 buradayim\n");
				free(g_ms.export[check_export]);
				g_ms.export[check_export] = ft_strdup(input[i]);
			}
			else
			{
				printf("6.2 buradayim\n");
				if (check_export != -2)
					add_export(input[i]);
			}
		}
		printf("7 buradayim\n");
		i++;
	}
}

void	add_env(char *input)
{
	int		i;
	char	**new_env;

	i = -1;
	new_env = ft_calloc(sizeof(char *), env_len() + 2);
	while (g_ms.ev[++i])
		new_env[i] = ft_strdup(g_ms.ev[i]);
	new_env[i] = ft_strdup(input);
	free_array(g_ms.ev);
	g_ms.ev = new_env;
}
/*
-> export;
-> new input added;
-> export = sıralanmış export (fonksiyon)
*/

void	add_export(char *input)
{
	char	**new_export;
	int		i;

	i = -1;
	new_export = ft_calloc(sizeof(char *), ft_get_arg_count(g_ms.export) + 2);
	while (g_ms.export[++i])
		new_export[i] = ft_strdup(g_ms.export[i]);
	new_export[i] = ft_strdup(input);
	free_array(g_ms.export);
	g_ms.export = new_export;
	ft_sort_export();
}

void	ft_sort_export(void)
{
	char	*tmp;
	int		i;
	int		j;
	int		size;

	i = 0;
	size = ft_get_arg_count(g_ms.export);
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(g_ms.export[i], g_ms.export[j]) > 0)
			{
				tmp = g_ms.export[i];
				g_ms.export[i] = g_ms.export[j];
				g_ms.export[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
