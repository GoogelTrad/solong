/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 12:19:45 by cmichez           #+#    #+#             */
/*   Updated: 2023/01/31 13:16:08 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	mv_forward(t_program *program)
{
	int		x;
	int		y;
	char	temp_y;

	x = program->player.pos_x;
	y = program->player.pos_y;
	temp_y = program->map[y][x];
	if (program->map[y - 1][x] == '0' || program->map[y - 1][x] == 'C')
	{
		program->map[y - 1][x] = '0';
		program->map[y][x] = program->map[y - 1][x];
		program->map[y - 1][x] = temp_y;
		program->player.pos_y = y - 1;
		program->move++;
	}
	else if (check_exit(program))
	{
		program->map[y - 2][x] = '0';
		program->map[y][x] = program->map[y - 2][x];
		program->map[y - 2][x] = temp_y;
		program->player.pos_y = y - 2;
		program->move++;
	}
	else if (program->map[y - 1][x] == 'E' && !(check_conso(program)))
	{
		write(1, "Bien joué, vous avez réussi à vous échapper !\n", 51);
		close_wd(program);
	}
	return (1);
}

int	mv_left(t_program *program)
{
	int		x;
	int		y;
	char	temp_x;

	x = program->player.pos_x;
	y = program->player.pos_y;
	temp_x = program->map[y][x];
	if (program->map[y][x - 1] == '0' || program->map[y][x - 1] == 'C')
	{
		program->map[y][x - 1] = '0';
		program->map[y][x] = program->map[y][x - 1];
		program->map[y][x - 1] = temp_x;
		program->player.pos_x = x - 1;
		program->move++;
	}
	else if (check_exit(program))
	{
		program->map[y][x - 2] = '0';
		program->map[y][x] = program->map[y][x - 2];
		program->map[y][x - 2] = temp_x;
		program->player.pos_x = x - 2;
		program->move++;
	}
	else if (program->map[y][x - 1] == 'E' && !(check_conso(program)))
	{
		write(1, "Bien joué, vous avez réussi à vous échapper !\n", 51);
		close_wd(program);
	}
	return (1);
}

int	mv_right(t_program *program)
{
	int		x;
	int		y;
	char	temp_x;

	x = program->player.pos_x;
	y = program->player.pos_y;
	temp_x = program->map[y][x];
	if (program->map[y][x + 1] == '0' || program->map[y][x + 1] == 'C')
	{
		program->map[y][x + 1] = '0';
		program->map[y][x] = program->map[y][x + 1];
		program->map[y][x + 1] = temp_x;
		program->player.pos_x = x + 1;
		program->move++;
	}
	else if (check_exit(program))
	{
		program->map[y][x + 2] = '0';
		program->map[y][x] = program->map[y][x + 2];
		program->map[y][x + 2] = temp_x;
		program->player.pos_x = x + 2;
		program->move++;
	}
	else if (program->map[y][x + 1] == 'E' && !(check_conso(program)))
	{
		write(1, "Bien joué, vous avez réussi à vous échapper !\n", 50);
		close_wd(program);
	}
	return (1);
}

int	mv_backward(t_program *program)
{
	int		x;
	int		y;
	char	temp_y;

	x = program->player.pos_x;
	y = program->player.pos_y;
	temp_y = program->map[y][x];
	if (program->map[y + 1][x] == '0' || program->map[y + 1][x] == 'C')
	{
		program->map[y + 1][x] = '0';
		program->map[y][x] = program->map[y + 1][x];
		program->map[y + 1][x] = temp_y;
		program->player.pos_y = y + 1;
		program->move++;
	}
	else if (check_exit(program))
	{
		program->map[y + 2][x] = '0';
		program->map[y][x] = program->map[y + 2][x];
		program->map[y + 2][x] = temp_y;
		program->player.pos_y = y + 2;
		program->move++;
	}
	else if (program->map[y + 1][x] == 'E' && !(check_conso(program)))
	{
		write(1, "Bien joué, vous avez réussi à vous échapper !\n", 51);
		close_wd(program);
	}
	return (1);
}

void	not_caracter(t_program *program, char element)
{
	if (element != '1' && element != '0' && element != 'P'
		&& element != 'C' && element != 'E' && element != '\n')
	{
		error_message("caractere");
		close_wd(program);
	}
}
