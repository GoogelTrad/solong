/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:12:11 by cmichez           #+#    #+#             */
/*   Updated: 2023/02/03 00:44:35 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

t_window	new_window(t_program *program, int widht, int height, char *name)
{
	t_window	window;

	window.reference = mlx_new_window(program->mlx, widht, height, name);
	window.size.x = widht;
	window.size.y = height;
	return (window);
}

int	close_wd(t_program *program)
{
	free_map(program->map);
	free(program);
	exit(0);
}

int	key_check(int keycode, t_program *program)
{
	if (keycode == 13)
		move(program, -1, 0);
	else if (keycode == 2)
		move(program, 0, 1);
	else if (keycode == 0)
		move(program, 0, -1);
	else if (keycode == 1)
		move(program, 1, 0);
	else if (keycode == 53)
	{
		write(1, "Arret du programme\n", 19);
		free(program);
		exit(0);
	}
	update_map(program);
	return (0);
}

void	charge_image(t_program *program)
{
	program->stock.arbre = new_sprite(program->mlx,
			"./images/objects/big_tree/arbre.xpm");
	program->stock.chest = new_sprite(program->mlx,
			"./images/objects/chest/chest_1.xpm");
	program->stock.player = new_sprite(program->mlx,
			"./images/entity/characters/player/backward_off_1.xpm");
	program->stock.sol = new_sprite(program->mlx,
			"./images/tilesets/floors/grass.xpm");
	program->stock.sortie = new_sprite(program->mlx,
			"./images/tilesets/floors/hole.xpm");
	program->player.bd = new_sprite(program->mlx,
			"./images/entity/characters/player/backward_off_1.xpm");
	program->player.fd = new_sprite(program->mlx,
			"./images/entity/characters/player/forward_off_1.xpm");
	program->player.lt = new_sprite(program->mlx,
			"./images/entity/characters/player/left_off_1.xpm");
	program->player.rt = new_sprite(program->mlx,
			"./images/entity/characters/player/right_off_1.xpm");
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
