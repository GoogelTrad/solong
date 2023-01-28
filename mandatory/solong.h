/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:00:16 by cmichez           #+#    #+#             */
/*   Updated: 2023/01/27 16:09:47 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define ARGUMENTS "Arguments incorrects !\n"
# define MAUVAIS "Map introuvable, mauvais nom de fichier ?\n"
# define CHEMIN "La map ne peut pas etre resolu !\n"
# define CARACTERE "Caractere inconnu dans la map !\n"
# define MUR "La map n'est pas entouré de mur !\n"
# define EXTENSION "Mauvaise extension de fichier !\n"
# define RECTANGLE "La map n'est pas rectangulaire !\n"
# define VIDE "La map donnee est vide !\n"

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
	t_image		fd;
	t_image		bd;
	t_image		lt;
	t_image		rt;
	t_vector	vector;
}				t_player;

typedef struct s_program
{
	void		*mlx;
	int			x;
	int			y;
	int			move;
	char		**map;
	int			p_map;
	int			c_map;
	int			e_map;
	t_window	window;
	t_image		sprite;
	t_vector	sprite_position;
	t_vector	img_pos;
	t_player	player;
	t_stock		stock;
}				t_program;
//game.c x
void		start_game(char *ficher_ber);
char		**init_map(t_program *program);
void		affiche_map(t_program *program);
void		update_map(t_program *program);
t_program	*calcul_map(t_program *program, char *fichier_ber);
//window.c x
int			close_wd(t_program *program);
t_window	new_window(t_program *program, int widht, int height, char *name);
int			key_check(int keycode, t_program *program);
void		charge_image(t_program *program);
void		free_map(char **map);
//image.c
t_image		new_sprite(void *mlx, char *path);
t_image		new_image(void *mlx, int widht, int height);
void		put_img(t_program *program, t_image img, int x, int y);
//floors.c x
void		put_floor(t_program *program, int x, int y);
void		put_element_map(t_program *program, char element, int x, int y);
//parsing.c x
char		*get_next_line(int fd);
void		reset_buffer(char *buffer);
int			check_buffer(char **line, char *tmp);
//utils.c x 
int			ft_strlen(char *str);
char		*ft_strcat(char *dest, char *src);
char		*ft_strcpy(char *dest, char *src);
char		*ft_strncat(char *dest, char *src, int n);
char		*ft_strdup(char *s);
//map.c x 
char		**mapping(t_program *program, char *fichier_ber);
char		**malloc_map(char *fichier_ber);
int			check_map(t_program *program);
int			nb_lignes_fd(char *fichier_ber);
int			map_error(int player, int sortie, int conso);
//player.c
int			mv_forward(t_program *program);
int			mv_left(t_program *program);
int			mv_right(t_program *program);
int			mv_backward(t_program *program);
void		not_caracter(t_program *program, char element);
//event.c x
int			open_chest(t_program *program);
int			check_conso(t_program *program);
void		printf_shell_mv(int compteur);
void		ft_putchar(char c);
//resolver.c x
int			verif_mur(t_program *program);
void		resolv_map(t_program *program);
int			path_finding(t_program *program, char **map, int x, int y);
char		**copy_map(t_program *program);
char		*ft_strncpy(char *dest, char *src, int n);
//main.c
void		check_extension(char *extension, char *fichier);
void		error_message(char *type);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

#endif