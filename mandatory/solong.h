/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:00:16 by cmichez           #+#    #+#             */
/*   Updated: 2023/01/15 15:34:08 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../mlx/mlx.h"

typedef struct s_vector
{
	int	x;
	int	y;
}		t_vector;

typedef struct s_window
{
	void		*reference;
	t_vector	size;
}				t_window;

typedef struct s_image
{
	void		*reference;
	t_vector	size;
	char		*pixels;
	int			bpp;
	int			line_size;
	int			endian;
}				t_image;

typedef struct s_stock
{
	t_image	sol;
	t_image	player;
	t_image	arbre;
	t_image	chest;
	t_image	sortie;
}			t_stock;

typedef struct s_player
{
	int			pos_x;
	int			pos_y;
	t_vector	vector;
}				t_player;

typedef struct s_program
{
	void		*mlx;
	int			move;
	char		**map;
	t_window	window;
	t_image		sprite;
	t_vector	sprite_position;
	t_vector	img_pos;
	t_player	player;
	t_stock		stock;
}				t_program;
//game.c
void		start_game(char *ficher_ber);
char		**init_map(t_program *program);
t_program	*calcul_map(t_program *program, char *fichier_ber);
void		affiche_map(char **map);
void		update_map(t_program *program);
//window.c
int			close_wd(void);
t_window	new_window(t_program *program, int widht, int height, char *name);
int			key_check(int keycode, t_program *program);
void		charge_image(t_program *program);
//image.c
t_image		new_sprite(void *mlx, char *path);
t_image		new_image(void *mlx, int widht, int height);
void		put_img(t_program *program, t_image img, int x, int y);
//floors.c
void		put_floor(t_program *program, int x, int y);
void		put_element_map(t_program *program, char element, int x, int y);
//parsing.c
char		*get_next_line(int fd);
void		reset_buffer(char *buffer);
int			check_buffer(char **line, char *tmp);
//utils.c
int			ft_strlen(char *str);
char		*ft_strcat(char *dest, char *src);
char		*ft_strcpy(char *dest, char *src);
char		*ft_strncpy(char *dest, char *src, int n);
char		*ft_strncat(char *dest, char *src, int n);
//map.c
char		**mapping(t_program *program, char *fichier_ber);
char		**malloc_map(char *fichier_ber);
int			nb_lignes_fd(char *fichier_ber);
int			check_map(char **map, t_program *program);
int			map_error(int player, int sortie, int conso);
//player.c
int			mv_forward(t_program *program);
int			mv_left(t_program *program);
int			mv_right(t_program *program);
int			mv_backward(t_program *program);
//event.c
int			open_chest(t_program *program);
int			check_conso(t_program *program);
void		printf_shell_mv(int compteur);
void		ft_putchar(char c);
//resolver.c
int			verif_mur(t_program *program);
int			verif_autour(t_program *program, int x, int y);
int			map_possible(t_program *program);
void		count_map(t_program *program, int *x, int *y);
//main.c
void		check_extension(char *extension, char *fichier);
void		error_message(char *type);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

#endif