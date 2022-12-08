# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sojoo <sojoo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/19 18:22:58 by heeskim           #+#    #+#              #
#    Updated: 2022/12/08 19:36:52 by sojoo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = cub3D
CFLAGS = -Wall -Wextra -Werror -O3 -g -fsanitize=address
DIR_MLX = mlx
MLX_LIB = libmlx.dylib
DIR_S = sources
DIR_G = gnl
SOURCES = hook.c main.c parse.c raycasting.c parse_util.c ft_util.c \
		ft_str_util.c raycasting_util.c ft_split.c parse_assign.c parse_check.c \
		parse_line.c parse_map.c draw.c mlx.c util.c
GNL_SOURCES = get_next_line.c get_next_line_utils.c
SRCS = $(addprefix $(DIR_S)/,$(SOURCES))
GSRCS = $(addprefix $(DIR_G)/,$(GNL_SOURCES))
OBJS = $(SRCS:.c=.o)
GOBJS = $(GSRCS:.c=.o)

all : $(NAME)

$(MLX_LIB) :
	@make -C $(DIR_MLX)
	@cp $(DIR_MLX)/$(MLX_LIB) .

$(NAME): $(OBJS) $(GOBJS)
	make $(MLX_LIB)
	$(CC) $(CFLAGS) -L$(DIR_MLX) -lmlx -framework OpenGL -framework Appkit $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(GOBJS)
	make clean -C $(DIR_MLX)
	rm -f $(MLX_LIB)

fclean: clean
	rm -f $(NAME)

re: 
	make fclean 
	make all

.PHONY: all, clean, fclean, re
