/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 17:07:23 by cmichez           #+#    #+#             */
/*   Updated: 2023/01/21 17:17:13 by cmichez          ###   ########.fr       */
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
		close_wd(program);
	//resolv_map(program);
	write(1, "4", 1);
	program->window = new_window(program, program->window.size.x,
			program->window.size.y, "./so_long");
	write(1, "5", 1);
	charge_image(program);
	write(1, "6", 1);
	program->map = init_map(program);
	write(1, "7", 1);
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
	if (check_map(program))
		close_wd(program);
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
	put_text(program, 10, 10);
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
		while (program->map[y][x] != '\n')
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
	int	temp_x;
	int	y;
	int	i;

	program->map = mapping(program, fichier_ber);
	x = ft_strlen(program->map[0]);
	i = 0;
	y = nb_lignes_fd(fichier_ber);
	temp_x = x;
	while (i < y)
	{
		//printf("i = %d, y = %d\n", i, y);
		x = ft_strlen(program->map[i]);
		//if ((i + 1) == y)
		//	temp_x--;
		//printf("x= %d, temp = %d\n", x, temp_x);
		if (temp_x != x)
		{
			error_message("rectangle");
			close_wd(program);
		}
		i++;
	}
	program->window.size.x = (temp_x - 1) * 46;
	program->window.size.y = y * 48;
	return (program);
}
