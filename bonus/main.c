/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:10:48 by cmichez           #+#    #+#             */
/*   Updated: 2023/01/19 16:08:34 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	main(int argc, char **argv)
{
	if (argc)
		check_extension("ber", argv[1]);
	return (0);
}

void	check_extension(char *extension, char *fichier)
{
	int	i;
	int	j;

	i = 0;
	while (fichier[i])
	{	
		if (fichier[i] == '.')
		{	
			i++;
			j = 0;
			while (fichier[i++] == extension[j] && j < 3)
				j++;
			if (j == 3)
			{
				if (open(fichier, O_RDONLY) == -1)
					error_message("mauvais");
				else
					start_game(fichier);
				break ;
			}
			else
				error_message("extension");
		}
		i++;
	}
}

void	error_message(char *type)
{
	write(1, "Error\n", 6);
	if (ft_strncmp(type, "extension", 10) == 0)
		write(1, "Mauvaise extension de fichier\n", 30);
	else if (ft_strncmp(type, "mauvais", 7) == 0)
		write(1, "Map introuvable, mauvais nom de fichier ?\n", 42);
	else if (ft_strncmp(type, "chemin", 6) == 0)
		write(1, "La map ne peut pas etre resolu !\n", 33);
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
