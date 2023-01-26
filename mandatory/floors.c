/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 18:03:22 by cmichez           #+#    #+#             */
/*   Updated: 2023/01/25 14:55:55 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	put_floor(t_program *program, int x, int y)
{
	while (x <= program->window.size.x)
	{
		y = 0;
		while (y <= program->window.size.y)
		{
			put_img(program, program->stock.sol, x, y);
			y += 48;
		}
		x += 48;
	}
}

void	put_element_map(t_program *program, char element, int x, int y)
{
	int	temp_x;
	int	temp_y;

	temp_x = program->img_pos.x;
	temp_y = program->img_pos.y;
	if (element == '1')
		put_img(program, program->stock.arbre, program->img_pos.x,
			program->img_pos.y);
	else if (element == 'C')
		put_img(program, program->stock.chest, temp_x + 12, temp_y + 24);
	else if (element == 'P')
	{
		put_img(program, program->stock.player, program->img_pos.x,
			program->img_pos.y);
		program->player.pos_x = x;
		program->player.pos_y = y;
	}
	else if (element == 'E')
		put_img(program, program->stock.sortie, program->img_pos.x,
			temp_y + 15);
}
