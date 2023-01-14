/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 12:19:45 by cmichez           #+#    #+#             */
/*   Updated: 2023/01/13 13:39:47 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	mv_forward(t_program *program)
{
	int		x;
	int		y;
	char	temp_y;

	x = program->player.pos_x;
	y = program->player.pos_y;
	temp_y = program->map[y][x];
	if (program->map[y - 1][x] == 'E' && !(check_conso(program)))
	{
		write(1, "Bien joué, vous avez réussi à vous échappez !\n", 51);
		exit(0);
	}
	else if ((program->map[y - 1][x] == '0') & touching_mob(program, x, y - 1))
	{
		program->map[y][x] = program->map[y - 1][x];
		program->map[y - 1][x] = temp_y;
		program->player.pos_y = y - 1;
		program->move++;
	}
	program->stock.player = program->player.fd;
	return (1);
}

int	mv_left(t_program *program)
{
	int		x;
	int		y;
	char	temp_x;

	x = program->player.pos_x;
	y = program->player.pos_y;
	temp_x = program->map[y][x];
	if (program->map[y][x - 1] == 'E' && !(check_conso(program)))
	{
		write(1, "Bien joué, vous avez réussi à vous échappez !\n", 51);
		exit(0);
	}
	else if ((program->map[y][x - 1] == '0') & touching_mob(program, x - 1, y))
	{
		program->map[y][x] = program->map[y][x - 1];
		program->map[y][x - 1] = temp_x;
		program->player.pos_x = x - 1;
		program->move++;
	}
	program->stock.player = program->player.lt;
	return (1);
}

int	mv_right(t_program *program)
{
	int		x;
	int		y;
	char	temp_x;

	x = program->player.pos_x;
	y = program->player.pos_y;
	temp_x = program->map[y][x];
	if (program->map[y][x + 1] == 'E' && !(check_conso(program)))
	{
		write(1, "Bien joué, vous avez réussi à vous échappez !\n", 50);
		exit(0);
	}
	else if ((program->map[y][x + 1] == '0') & touching_mob(program, x + 1, y))
	{
		program->map[y][x] = program->map[y][x + 1];
		program->map[y][x + 1] = temp_x;
		program->player.pos_x = x + 1;
		program->move++;
	}
	program->stock.player = program->player.rt;
	return (1);
}

int	mv_backward(t_program *program)
{
	int		x;
	int		y;
	char	temp_y;

	x = program->player.pos_x;
	y = program->player.pos_y;
	temp_y = program->map[y][x];
	if (program->map[y + 1][x] == 'E' && !(check_conso(program)))
	{
		write(1, "Bien joué, vous avez réussi à vous échappez !\n", 51);
		exit(0);
	}
	else if ((program->map[y + 1][x] == '0') & touching_mob(program, x, y + 1))
	{
		program->map[y][x] = program->map[y + 1][x];
		program->map[y + 1][x] = temp_y;
		program->player.pos_y = y + 1;
		program->move++;
	}
	program->stock.player = program->player.bd;
	return (1);
}
