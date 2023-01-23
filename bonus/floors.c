/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 18:03:22 by cmichez           #+#    #+#             */
/*   Updated: 2023/01/23 13:18:04 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	put_floor(t_program *program, int x, int y)
{
	while (x <= program->window.size.x)
	{
		y = 0;
		while (y <= program->window.size.y)
		{
			put_img(program, program->stock.sol, x, y);
			y += 48;
		}
		x += 48;
	}
}

void	put_element_map(t_program *program, char element, int x, int y)
{
	int	temp_x;
	int	temp_y;

	temp_x = program->img_pos.x;
	temp_y = program->img_pos.y;
	if (element == '1')
		put_img(program, program->stock.arbre, program->img_pos.x,
			program->img_pos.y);
	else if (element == 'C')
		put_img(program, program->stock.chest, temp_x + 12, temp_y + 24);
	else if (element == 'P')
	{
		put_img(program, program->stock.player, program->img_pos.x,
			program->img_pos.y);
		program->player.pos_x = x;
		program->player.pos_y = y;
	}
	else if (element == 'E')
		put_img(program, program->stock.sortie, program->img_pos.x,
			temp_y + 15);
	else if (element == 'M')
		put_img(program, program->stock.mob, temp_x + 10, temp_y + 20);
}

void	put_text(t_program *program, int x, int y)
{
	char	*pas;

	pas = ft_itoa(program->move);
	mlx_string_put(program->mlx, program->window.reference, x, y,
		0x00FF1F1F, pas);
	free(pas);
}

int	count_size(int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n / 10)
	{
		i++;
		n /= 10;
	}
	return (i + 1);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*str;
	long	nb;

	i = count_size(n);
	nb = n;
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (0);
	if (n < 0)
		nb *= -1;
	str[i--] = '\0';
	while (i >= 0)
	{
		str[i] = nb % 10 + 48;
		nb /= 10;
		i--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
