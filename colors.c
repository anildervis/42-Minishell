/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binurtas <binurtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:17:39 by binurtas          #+#    #+#             */
/*   Updated: 2023/05/20 14:24:11 by binurtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	print_part1(void)
{
	printf("\033[0mabow\033[0m ");
	printf("\033[1mabow\033[0m ");
	printf("\033[2mabow\033[0m ");
	printf("\033[3mabow\033[0m ");
	printf("\033[4mabow\033[0m ");
	printf("\033[5mabow\033[0m\n");
	printf("\033[6mabow\033[0m ");
	printf("\033[7mabow\033[0m ");
	printf("\033[8mabow\033[0m ");
	printf("\033[9mabow\033[0m ");
	printf("\033[10mabow\033[0m ");
	printf("\033[11mabow\033[0m\n");
	printf("\033[12mabow\033[0m ");
	printf("\033[13mabow\033[0m ");
	printf("\033[14mabow\033[0m ");
	printf("\033[15mabow\033[0m ");
	printf("\033[16mabow\033[0m ");
}

void	print_part2(void)
{
	printf("\033[17mabow\033[0m\n");
	printf("\033[18mabow\033[0m ");
	printf("\033[19mabow\033[0m ");
	printf("\033[21mabow\033[0m ");
	printf("\033[23mabow\033[0m ");
	printf("\033[24mabow\033[0m ");
	printf("\033[25mabow\033[0m\n");
	printf("\033[26mabow\033[0m ");
	printf("\033[27mabow\033[0m ");
	printf("\033[28mabow\033[0m ");
	printf("\033[29mabow\033[0m ");
	printf("\033[30mabow\033[0m ");
	printf("\033[31mabow\033[0m\n");
	printf("\033[32mabow\033[0m ");
	printf("\033[33mabow\033[0m ");
	printf("\033[34mabow\033[0m ");
	printf("\033[35mabow\033[0m ");
	printf("\033[36mabow\033[0m ");
}

int	main(void)
{
	print_part1();
	print_part2();
	return (0);
}
