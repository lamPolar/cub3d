# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/19 18:22:58 by heeskim           #+#    #+#              #
#    Updated: 2022/10/19 10:04:50 by heeskim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = cub3d
CFLAGS = -Wall -Wextra -Werror -O3
DIR_MLX = mlx
MLX_LIB = libmlx.dylib
DIR_S = sources
SOURCES = main.c parse.c raycasting.c util.c
SRCS = $(addprefix $(DIR_S)/,$(SOURCES))
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(MLX_LIB) :
	@make -C $(DIR_MLX)
	@cp $(DIR_MLX)/$(MLX_LIB) .

$(NAME): $(OBJS)
	make $(MLX_LIB)
	$(CC) $(CFLAGS) -L$(DIR_MLX) -lmlx -framework OpenGL -framework Appkit $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make clean -C $(DIR_MLX)
	rm -f $(MLX_LIB)

fclean: clean
	rm -f $(NAME)

re: 
	make fclean 
	make all

.PHONY: all, clean, fclean, re
