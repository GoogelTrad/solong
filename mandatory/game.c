/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 17:07:23 by cmichez           #+#    #+#             */
/*   Updated: 2023/01/25 15:06:52 by cmichez          ###   ########.fr       */
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
	if (verif_mur(program))
	{
		error_message("mur");
		close_wd(program);
	}
	resolv_map(program);
	program->window = new_window(program, program->window.size.x,
			program->window.size.y, "./so_long");
	charge_image(program);
	program->map = init_map(program);
	mlx_hook(program->window.reference, 17, 0, close_wd, program);
	mlx_hook(program->window.reference, 2, 0, key_check, program);
	mlx_loop(program->mlx);
}

char **init_map(t_program *program)
{
	int	x;
	int	y;

	y = 0;
	if (check_map(program))
		close_wd(program);
	put_floor(program, 0, 0);
	program->img_pos.y = 0;
	while (program->map[y])
	{
		x = 0;
		program->img_pos.x = 0;
		while (program->map[y][x] && program->map[y][x] != '\n')
		{
			put_element_map(program, program->map[y][x], x, y);
			program->img_pos.x += 46;
			x++;
		}
		y++;
		program->img_pos.y += 48;
	}
	return (program->map);
}

void	update_map(t_program *program)
{
	int	x;
	int	y;

	y = 0;
	put_floor(program, 0, 0);
	program->img_pos.y = 0;
	while (program->map[y])
	{
		x = 0;
		program->img_pos.x = 0;
		while (program->map[y][x] && program->map[y][x] != '\n')
		{
			put_element_map(program, program->map[y][x], x, y);
			program->img_pos.x += 46;
			x++;
		}
		y++;
		program->img_pos.y += 48;
	}
}

void	affiche_map(t_program *program)
{
	int	x;
	int	y;

	y = 0;
	write(1, "\n", 1);
	while (program->map[y])
	{
		x = 0;
		while (program->map[y][x] != '\n' && program->map[y][x])
		{
			write(1, " ", 1);
			write(1, &program->map[y][x], 1);
			x++;
		}
		write(1, "\n", 1);
		y++;
	}
	write(1, "\n", 2);
}

t_program	*calcul_map(t_program *program, char *fichier_ber)
{
	int	x;
	int	y;
	int	i;

	program->map = mapping(program, fichier_ber);
	x = ft_strlen(program->map[0]);
	i = 0;
	y = nb_lignes_fd(fichier_ber);
	while (i < y - 1)
	{
		if (ft_strlen(program->map[i]) != x)
		{
			error_message("rectangle");
			close_wd(program);
		}
		i++;
	}
	if (ft_strlen(program->map[i]) != x - 1)
	{
		error_message("rectangle");
		close_wd(program);
	}
	program->window.size.x = (x - 1) * 46;
	program->window.size.y = y * 48;
	return (program);
}
