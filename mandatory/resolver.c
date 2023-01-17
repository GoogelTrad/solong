/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:16:14 by cmichez           #+#    #+#             */
/*   Updated: 2023/01/17 12:44:46 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

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

void get_pos(t_program *program, int *x, int *y, char element)
{
	program->img_pos.x = 0;
	program->img_pos.x = 0;
	
	while (program->map[program->img_pos.y][program->img_pos.x] != '\0')
	{
		if (program->map[program->img_pos.y][program->img_pos.x] == element)
		{
			*x = program->img_pos.x;
			*y = program->img_pos.y;
		}
		else if (program->map[program->img_pos.y][program->img_pos.x] == '\n')
		{
			program->img_pos.x = 0;
			program->img_pos.y++;
		}
		program->img_pos.x++;
	}
}

void	revolv_map(t_program *program)
{
	int	pos_x;
	int	pos_y;

	pos_x = 0;
	pos_y = 0;
	program->img_pos.x = 0;
	program->img_pos.x = 0;
	get_pos(program, &pos_x, &pos_y, 'P');
	while (program->map[program->img_pos.y][program->img_pos.x] != '\0')
	{
		if ()
		{
			
		}
		else if(program->map[program->img_pos.y][program->img_pos.x] == '\n')
		{
			program->img_pos.x = 0;
			program->img_pos.y++;
		}
		program->img_pos.x++;
	}
}