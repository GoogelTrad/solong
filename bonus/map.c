/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 22:12:58 by cmichez           #+#    #+#             */
/*   Updated: 2023/01/21 17:16:52 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

char	**mapping(t_program *program, char *fichier_ber)
{
	int	fd;

	fd = open(fichier_ber, O_RDONLY);
	if (fd)
		write(1, "La map a pu être ouverte correctement !\n", 42);
	else
		write(1, "Il y a eu un problème lors de l'ouverture de la map /n", 56);
	program->map = malloc_map(fichier_ber);
	return (program->map);
}

char	**malloc_map(char *fichier_ber)
{
	char	**map;
	int		fd;
	int		ligne;
	int		i;

	ligne = nb_lignes_fd(fichier_ber) + 1;
	i = 0;
	fd = open(fichier_ber, O_RDONLY);
	map = malloc(sizeof(char *) * (ligne + 1));
	while (i < ligne)
	{
		map[i] = get_next_line(fd);
		i++;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

int	nb_lignes_fd(char *fichier_ber)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = open(fichier_ber, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		i++;
		line = get_next_line(fd);
	}
	if (!line)
		i--;
	free(line);
	close(fd);
	return (i);
}

int	check_map(t_program *program)
{
	program->c_map = 0;
	program->e_map = 0;
	program->p_map = 0;
	program->img_pos.x = 0;
	program->img_pos.y = 0;
	while (program->map[program->img_pos.y][program->img_pos.x] != '\0')
	{
		if (program->map[program->img_pos.y][program->img_pos.x] == 'P')
			program->p_map++;
		else if (program->map[program->img_pos.y][program->img_pos.x] == 'E')
			program->e_map++;
		else if (program->map[program->img_pos.y][program->img_pos.x] == 'C')
			program->c_map++;
		else if (program->map[program->img_pos.y][program->img_pos.x] == '\n')
		{
			program->img_pos.x = 0;
			program->img_pos.y++;
		}
		not_caracter(program,
			program->map[program->img_pos.y][program->img_pos.x]);
		program->img_pos.x++;
	}
	return (map_error(program->p_map, program->e_map, program->c_map));
}

int	map_error(int player, int sortie, int conso)
{
	if (player != 1 || sortie != 1 || conso < 1)
	{
		write(1, "Error\n", 6);
		if (player != 1)
			write(1, "Nombre de P incorrecte !\n", 25);
		if (sortie != 1)
			write(1, "Nombre de E incorrecte !\n", 25);
		if (conso < 1)
			write(1, "Nombre de C incorrecte !\n", 25);
		return (1);
	}
	return (0);
}
