/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 17:07:23 by cmichez           #+#    #+#             */
/*   Updated: 2023/01/14 09:56:24 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	start_game(char *ficher_ber)
{
	t_program	*program;

	program = malloc(sizeof(t_program));
	program->move = 0;
	program->mlx = mlx_init();
	program = calcul_map(program, ficher_ber);
	if (map_possible(program))
	{
		error_message("chemin");
		exit(0);
	}
	program->window = new_window(program, program->window.size.x,
			program->window.size.y, "./so_long");
	charge_image(program);
	program->map = init_map(program);
	mlx_hook(program->window.reference, 17, 0, close_wd, program);
	mlx_hook(program->window.reference, 2, 0, key_check, program);
	mlx_loop(program->mlx);
}

char	**init_map(t_program *program)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	if (check_map(program->map, program))
		close_wd();
	put_floor(program, 0, 0);
	program->img_pos.x = 0;
	program->img_pos.y = 0;
	while (program->map[y][x] != '\0')
	{
		put_element_map(program, program->map[y][x], x, y);
		program->img_pos.x += 46;
		x++;
		if (program->map[y][x] == '\n')
		{
			y++;
			program->img_pos.y += 48;
			program->img_pos.x = 0;
			x = 0;
		}
	}
	return (program->map);
}

void	update_map(t_program *program)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	program->img_pos.x = 0;
	program->img_pos.y = 0;
	put_floor(program, 0, 0);
	while (program->map[y][x] != '\0')
	{
		put_element_map(program, program->map[y][x], x, y);
		program->img_pos.x += 46;
		x++;
		if (program->map[y][x] == '\n')
		{
			y++;
			program->img_pos.y += 48;
			program->img_pos.x = 0;
			x = 0;
		}
	}
}

void	affiche_map(t_program *program)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	write(1, "\n", 1);
	while (program->map[x][y])
	{
		if (program->map[x][y] == '\n')
		{
			x++;
			y = 0;
			write(1, "\n", 1);
		}
		write(1, " ", 1);
		write(1, &program->map[x][y], 1);
		y++;
	}
	write(1, "\n\n", 2);
}

t_program	*calcul_map(t_program *program, char *fichier_ber)
{
	int	x;
	int	fd;
	int	temp_x;
	int	y;
	int	i;

	x = 0;
	i = 0;
	y = nb_lignes_fd(fichier_ber);
	temp_x = 0;
	program->map = mapping(program, fichier_ber);
	fd = open(fichier_ber, O_RDONLY);
	while (i < y)
	{
		x = ft_strlen(get_next_line(fd));
		if (temp_x < x)
			temp_x = x;
		i++;
	}
	program->window.size.x = (temp_x - 1) * 46;
	program->window.size.y = y * 48;
	close(fd);
	return (program);
}
