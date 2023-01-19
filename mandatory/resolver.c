/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:16:14 by cmichez           #+#    #+#             */
/*   Updated: 2023/01/19 15:51:58 by cmichez          ###   ########.fr       */
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

void	resolv_map(t_program *program)
{
	char	**map;

	if (verif_mur(program))
		error_message("chemin");
	program->img_pos.x = 0;
	program->img_pos.y = 0;
	while (program->map[program->img_pos.y][program->img_pos.x])
	{
		if (program->map[program->img_pos.y][program->img_pos.x] == 'C' ||
			program->map[program->img_pos.y][program->img_pos.x] == 'P')
		{
			map = copy_map(program);
			if (!path_finding(program, map, program->img_pos.x,
					program->img_pos.y))
				error_message("chemin");
			free(map);
		}
		else if (program->map[program->img_pos.y][program->img_pos.x] == '\n')
		{
			program->img_pos.x = 0;
			program->img_pos.y++;
		}
		program->img_pos.x++;
	}
}

int	path_finding(t_program *program, char **map, int x, int y)
{
	if (program->map[y][x] == 'E')
		return (1);
	if (program->map[y][x] == '1' || map[y][x] == '1')
		return (0);
	map[y][x] = '1';
	if (x != 0)
		if (path_finding(program, map, x - 1, y))
			return (1);
	if (map[y][x + 1] != '\n')
		if (path_finding(program, map, x + 1, y))
			return (1);
	if (y != 0)
		if (path_finding(program, map, x, y - 1))
			return (1);
	if (map[y + 1][x])
		if (path_finding(program, map, x, y + 1))
			return (1);
	return (0);
}

char	**copy_map(t_program *program)
{
	int		i;
	int		j;
	char	**map;

	j = program->window.size.y / 48;
	map = malloc(sizeof(char *) * (j + 1));
	i = 0;
	while (i < j)
	{
		map[i] = malloc(sizeof(char) * (ft_strlen(program->map[i]) + 1));
		map[i] = ft_strcpy(map[i], program->map[i]);
		i++;
	}
	map[i] = NULL;
	return (map);
}
