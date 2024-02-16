# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samoore <samoore@student.42london.com      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/23 12:40:32 by samoore           #+#    #+#              #
#    Updated: 2024/02/16 17:27:28 by samoore          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_FILES = fdf.c map.c split.c points.c lines.c file.c rotate.c kill.c mouse.c
OBJ_FILES = $(patsubst %.o, %.c, $(SRC_FILES))
MLX_FLAGS = -L. -lmlx -lXext -lX11 -lm -lft
C_FLAGS = -w -g3 -Wall -Werror -Wextra
INCLUDES = -I. -I/usr/include

NAME = a.out
CC = gcc

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(C_FLAGS) -o $(NAME) $(SRC_FILES) $(MLX_FLAGS)

.c.o:
	$(CC) $(C_FLAGS) -o $@ $< $(INCLUDES)

clean:
	rm
