/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:16:14 by cmichez           #+#    #+#             */
/*   Updated: 2023/01/18 16:25:50 by cmichez          ###   ########.fr       */
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

void	get_pos(char **map, int *x, int *y, char element)
{
	while (map[*y][*x] != element)
	{
		if (map[*y][*x] == '\n')
		{
			(*x) = 0;
			(*y)++;
		}
		(*x)++;
	}
}

void	resolv_map(t_program *program)
{
	char **map;
	int pos_x;
	int pos_y;

	program->img_pos.x = 0;
	program->img_pos.y = 0;
	map = copy_map(program);
	while (map[program->img_pos.y][program->img_pos.x])
	{
		pos_x = 0;
		pos_y = 0;
		if (map[program->img_pos.y][program->img_pos.x] == 'C')
		{
			get_pos(map, &pos_x, &pos_y, 'C');
			path_finding(program, map, pos_x, pos_y);
		}
		else if (map[program->img_pos.y][program->img_pos.x] == 'P')
		{
			get_pos(map, &pos_x, &pos_y, 'P');
			path_finding(program, map, pos_x, pos_y);
		}
		else if (map[program->img_pos.y][program->img_pos.x] == '\n')
		{
			program->img_pos.x = 0;
			program->img_pos.y++;
		}
		program->img_pos.x++;
	}
}

int path_finding(t_program *program, char **map, int x, int y)
{
	if (program->map[y][x] == 'E')
		return (1);
	if (program->map[y][x] == '1' || map[y][x] == '1')
		return (0);
	map[y][x] = '1';
	if (x != 0)
	{
		if (path_finding(program, map, x - 1, y))
			return (1);
	}
	if (x < (program->window.size.x / 46) - 1)
	{
		if (path_finding(program, map, x + 1, y))
			return (1);
	}
	if (y != 0)
	{
		if (path_finding(program, map, x, y - 1))
			return (1);
	}
	if (y < (program->window.size.y / 48) - 1)
	{
		if (path_finding(program, map, x, y + 1))
			return (1);
	}
	return (0);
}

char	**copy_map(t_program *program)
{
	int	i;
	char **map;

	i = 0;
	while (program->map[i])
		i++;
	map = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while(program->map[i])
	{
		map[i] = malloc(sizeof(char) * (ft_strlen(program->map[i]) + 1));
		map[i] = ft_strcpy(map[i], program->map[i]);
		i++;
	}
	return (map);
}