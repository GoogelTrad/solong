/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 11:27:36 by cmichez           #+#    #+#             */
/*   Updated: 2023/01/12 15:22:40 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

t_image	new_sprite(void *mlx, char *path)
{
	t_image	img;

	img.reference = mlx_xpm_file_to_image(mlx, path, &img.size.x,
			&img.size.y);
	img.pixels = mlx_get_data_addr(img.reference, &img.bpp,
			&img.line_size, &img.endian);
	return (img);
}

void	put_img(t_program *program, t_image img, int x, int y)
{
	mlx_put_image_to_window(program->mlx, program->window.reference,
		img.reference, x, y);
}
