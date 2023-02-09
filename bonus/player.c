/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 12:19:45 by cmichez           #+#    #+#             */
/*   Updated: 2023/02/03 19:49:17 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	move(t_program *program, int i, int j, int direction)
{
	int	x;
	int	y;
	int	increment;

	x = program->player.pos_x;
	y = program->player.pos_y;
	increment = 0;
	increment = increment_player(program, program->map[y + i][x + j],
			increment);
	if (program->map[y + (i * increment)][x + (j * increment)] != '1' &&
		program->map[y + (i * increment)][x + (j * increment)] != 'E' &&
		increment && touching_mob(program, x + (j * increment),
		y + (i * increment)))
	{
		program->stock.player = program->player.anime[direction];
		player_move(program, i, j, increment);
	}
	else if (program->map[y + (i * increment)][x + (j * increment)] == 'E'
		&& increment == 1)
	{
		write(1, "Bien joué, vous avez réussi à vous échapper !\n", 51);
		close_wd(program);
	}
	return (1);
}

void	player_move(t_program *program, int i, int j, int increment)
{
	int		x;
	int		y;
	char	temp;

	x = program->player.pos_x;
	y = program->player.pos_y;
	temp = program->map[y][x];
	if (program->map[y + (i * increment)][x + (j * increment)] == 'C')
		program->map[y + (i * increment)][x + (j * increment)] = '0';
	program->map[y][x] = program->map[y + (i * increment)][x + (j * increment)];
	program->map[y + (i * increment)][x + (j * increment)] = temp;
	program->player.pos_y = y + (i * increment);
	program->player.pos_x = x + (j * increment);
	program->move++;
	write(1, "Compteur de mouvement : ", 25);
	printf_shell_mv(program->move);
	write(1, "\n", 1);
}

int	increment_player(t_program *program, char element, int increment)
{
	if (element == 'E' && !(check_conso(program)))
		increment = 1;
	else if (element == 'E' && check_conso(program))
	{
		write(1, "Il reste des objets à prendre !\n", 34);
		increment = 2;
	}
	else if (element == '0' || element == 'C' || element == 'M')
		increment = 1;
	return (increment);
}

void	not_caracter(t_program *program, char element)
{
	if (element != 'M' && element != '1' && element != '0' && element != 'P'
		&& element != 'C' && element != 'E' && element != '\n')
	{
		error_message("caractere");
		close_wd(program);
	}
}

void	animation_stock(t_program *program)
{
	program->player.anime[0] = program->player.bd;
	program->player.anime[1] = program->player.rt;
	program->player.anime[2] = program->player.fd;
	program->player.anime[3] = program->player.lt;
}
