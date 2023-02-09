/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:18:20 by cmichez           #+#    #+#             */
/*   Updated: 2023/02/09 15:52:38 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	move_t(t_program *program)
{
	int	x;
	int	y;

	x = program->player.pos_x;
	y = program->player.pos_y;
	if (program->map[y - 1][x] == '1' && limit_wall(program, x, y - 1))
		program->map[y - 1][x] = '0';
	else if (program->map[y + 1][x] == '1' && limit_wall(program, x, y + 1))
		program->map[y + 1][x] = '0';
	else if (program->map[y][x - 1] == '1' && limit_wall(program, x - 1, y))
		program->map[y][x - 1] = '0';
	else if (program->map[y][x + 1] == '1' && limit_wall(program, x + 1, y))
		program->map[y][x + 1] = '0';
	return (1);
}

int	limit_wall(t_program *program, int x, int y)
{
	if (!(x > 0 && x < (program->window.size.x / 46) - 1))
		return (0);
	if (!(y > 0 && y < (program->window.size.y / 48) - 1))
		return (0);
	return (1);
}
