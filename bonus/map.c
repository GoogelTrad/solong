/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 22:12:58 by cmichez           #+#    #+#             */
/*   Updated: 2023/01/14 09:51:04 by cmichez          ###   ########.fr       */
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

	ligne = nb_lignes_fd(fichier_ber);
	i = 0;
	fd = open(fichier_ber, O_RDONLY);
	map = malloc(sizeof(char *) * ligne);
	while (i < ligne)
	{
		map[i] = get_next_line(fd);
		i++;
	}
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
	close(fd);
	return (i);
}

int	check_map(char **map, t_program *program)
{
	int	player;
	int	sortie;
	int	conso;

	program->img_pos.x = 0;
	program->img_pos.y = 0;
	player = 0;
	sortie = 0;
	conso = 0;
	while (map[program->img_pos.y][program->img_pos.x] != '\0')
	{
		if (map[program->img_pos.y][program->img_pos.x] == 'P')
			player++;
		else if (map[program->img_pos.y][program->img_pos.x] == 'E')
			sortie++;
		else if (map[program->img_pos.y][program->img_pos.x] == 'C')
			conso++;
		else if (map[program->img_pos.y][program->img_pos.x] == '\n')
		{
			program->img_pos.x = 0;
			program->img_pos.y++;
		}
		program->img_pos.x++;
	}
	return (map_error(player, sortie, conso));
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
