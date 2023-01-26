SRCS = mandatory/main.c mandatory/window.c mandatory/event.c mandatory/parsing.c mandatory/map.c mandatory/image.c mandatory/game.c mandatory/floors.c mandatory/player.c mandatory/utils.c mandatory/resolver.c mandatory/utils2.c
BONUS = bonus/main.c bonus/window.c bonus/event.c bonus/parsing.c bonus/map.c bonus/image.c bonus/game.c bonus/floors.c bonus/player.c bonus/utils.c bonus/resolver.c
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(BONUS:.c=.o)
CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = solong
NAME_BONUS = solong_bonus
MACLINKS = -Lmlx -lmlx -framework OpenGL -framework AppKit 
LLINKS = -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm
COMPIL_LINUX = -I/usr/include -Imlx_linux

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(OBJS) $(MACLINKS) -o $(NAME)

bonus: $(OBJS_BONUS)
	gcc $(OBJS_BONUS) $(MACLINKS) -o $(NAME_BONUS)

clean: 
	rm -rf $(OBJS) $(OBJS_BONUS)

fclean: clean 
	rm -rf $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all ${NAME} clean flcean re

%.o: %.c
	gcc $(FLAGS) -c $< -o $@