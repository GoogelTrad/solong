/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:16:14 by cmichez           #+#    #+#             */
/*   Updated: 2023/01/15 14:11:12 by cmichez          ###   ########.fr       */
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

int	resolv_map(t_program *program, int x, int y)
{
	char	**map_cpy;

	map_cpy = program->map;
	program->img_pos.x = x;
	program->img_pos.y = y;
	while (map_cpy[program->img_pos.y][program->img_pos.x])
	{
		if (map_cpy[program->img_pos.y][program->img_pos.x] == 'C')
			if (chemin_possible(program, map_cpy, program->img_pos.x, program->img_pos.y))
				return (1);
			
	}	
}

int	chemin_possible(t_program *program, char **map, int x, int y)
{
	while (map[y][x])
	{
		if(map[y + 1][x] == '0')
		{
			change_place(map, x, y, 1, 0);
		}
	}
}

void	change_place(char **map, int x, int y, int i, int j)
{
	char	temp;
	
	temp = map[y][x];
	map[y][x] = map[y + i][x + j];
	map[y + i][x + j] = temp;
}