/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:16:14 by cmichez           #+#    #+#             */
/*   Updated: 2023/01/13 11:09:13 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	map_possible(t_program *program)
{
	if (verif_mur(program))
		return (1);
	program->img_pos.x = 0;
	program->img_pos.y = 0;
	while (program->map[program->img_pos.y][program->img_pos.x++] != '\0')
	{
		if (program->map[program->img_pos.y][program->img_pos.x] == 'P'
			&& verif_autour(program, program->img_pos.x, program->img_pos.y))
			return (1);
		else if (program->map[program->img_pos.y][program->img_pos.x] == 'C'
			&& verif_autour(program, program->img_pos.x, program->img_pos.y))
			return (1);
		else if (program->map[program->img_pos.y][program->img_pos.x] == 'E'
			&& verif_autour(program, program->img_pos.x, program->img_pos.y))
			return (1);
		else if (program->map[program->img_pos.y][program->img_pos.x] == '\n')
		{
			program->img_pos.x = 0;
			program->img_pos.y++;
		}
	}
	return (0);
}

int	verif_autour(t_program *program, int x, int y)
{
	if (program->map[y + 1][x] == '1' && program->map[y - 1][x] == '1'
			&& program->map[y][x + 1] == '1' && program->map[y][x - 1] == '1')
		return (1);
	return (0);
}

int	verif_mur(t_program *program)
{
	int	temp_x;
	int	temp_y;

	program->img_pos.x = 0;
	program->img_pos.y = 0;
	temp_x = program->window.size.x / 46;
	temp_y = program->window.size.y / 48;
	while (program->img_pos.x < temp_x)
	{
		if (program->map[0][program->img_pos.x] != '1'
			|| program->map[temp_y - 1][program->img_pos.x] != '1')
			return (1);
		program->img_pos.x++;
	}
	program->img_pos.x--;
	while (program->img_pos.y < temp_y)
	{
		if (program->map[program->img_pos.y][0] != '1'
			|| program->map[program->img_pos.y][temp_x - 1] != '1')
			return (1);
		program->img_pos.y++;
	}
	return (0);
}
