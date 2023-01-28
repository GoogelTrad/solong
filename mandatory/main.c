/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:10:48 by cmichez           #+#    #+#             */
/*   Updated: 2023/01/27 16:08:03 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	main(int argc, char **argv)
{
	if (argc == 2)
		check_extension(".ber", argv[1]);
	else
		error_message(ARGUMENTS);
	return (0);
}

void	check_extension(char *extension, char *fichier)
{
	int	i;

	i = 0;
	while (fichier[i])
		i++;
	i -= ft_strlen(extension);
	if (strcmp(fichier + i, extension) != 0)
	{
		error_message(EXTENSION);
		exit(0);
	}
	if (read(open(fichier, O_RDONLY), 0, 0) == -1)
	{
		error_message(MAUVAIS);
		exit(0);
	}
	start_game(fichier);
}

void	error_message(char *type)
{
	write(1, "Error\n", 6);
	write(1, type, ft_strlen(type));
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				i;
	unsigned char	*c;
	unsigned char	*f;

	i = 0;
	c = (unsigned char *) s1;
	f = (unsigned char *) s2;
	while (c[i] && c[i] == f[i] && n > 0)
	{
		i++;
		n--;
	}
	if (n == 0)
		return (0);
	return (c[i] - f[i]);
}
