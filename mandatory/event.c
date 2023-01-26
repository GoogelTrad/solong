/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 14:32:36 by cmichez           #+#    #+#             */
/*   Updated: 2023/01/25 14:55:30 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	open_chest(t_program *program)
{
	int	x;
	int	y;

	x = program->player.pos_x;
	y = program->player.pos_y;
	if (program->map[y - 1][x] == 'C')
		program->map[y - 1][x] = '0';
	else if (program->map[y + 1][x] == 'C')
		program->map[y + 1][x] = '0';
	else if (program->map[y][x - 1] == 'C')
		program->map[y][x - 1] = '0';
	else if (program->map[y][x + 1] == 'C')
		program->map[y][x + 1] = '0';
	return (1);
}

int	check_conso(t_program *program)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (program->map[y][x] != '\0')
	{
		if (program->map[y][x] == '\n')
		{
			x = 0;
			y++;
		}
		else if (program->map[y][x] == 'C')
		{
			write(1, "Il reste des objets à prendre !\n", 34);
			return (1);
		}
		x++;
	}
	return (0);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	printf_shell_mv(int compteur)
{
	if (compteur == -2147483648)
		write(1, "-2147483648", 11);
	else
	{
		if (compteur < 0)
		{
			ft_putchar('-');
			compteur *= -1;
		}
		if (compteur >= 10)
		{
			printf_shell_mv(compteur / 10);
			printf_shell_mv(compteur % 10);
		}
		else
			ft_putchar(compteur + '0');
	}
}

