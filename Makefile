# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: parallels <parallels@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 14:32:36 by sasida            #+#    #+#              #
#    Updated: 2025/05/28 19:35:56 by parallels        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/
OBJ_DIR = obj/
CFLAGS = -Wall -Wextra -Werror -O2

SRCS = $(addprefix $(SRC), main.c \
		init.c \
		parsing/validation.c \
		parsing/load_map.c \
		parsing/reader.c \
		parsing/color_parser.c \
		parsing/texture_parser.c \
		parsing/parser.c \
		parsing/mapper.c \
		parsing/player.c \
		input/input.c \
		input/movement.c \
		input/rotation.c \
		map/map.c \
		map/collision.c \
		minimap/minimap.c \
		minimap/minimap_player.c \
		minimap/minimap_fov.c \
		minimap/minimap_render.c \
		minimap/minimap_utils.c \
		raycasting/ray_init_calc.c \
		raycasting/dda_and_height.c \
		raycasting/dda_utils.c \
		raycasting/raycasting_utils.c \
		textures/texture_manager.c \
		textures/texture_loader.c \
		textures/texture_data.c \
		textures/texture_calc.c \
		textures/texture_render.c \
		utils/cleanup.c \
		utils/array_utils.c \
		utils/memory_utils.c)

OBJS = $(SRCS:$(SRC)%.c=$(OBJ_DIR)%.o)

INCLUDES = -I ./include -I ./libft -I ./minilibx-linux
LIBFT = libft.a
LIB_DIR = ./libft
MINI_LIBX_DIR = ./minilibx-linux
MINI_LIBX = libmlx.a
NAME = cub3D

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MINI_LIBX)
	@if [ ! -f $(NAME) ] || [ -n "$$(find $(OBJS) -newer $(NAME) 2>/dev/null)" ]; then \
		$(CC) $(OBJS) $(CFLAGS) $(INCLUDES) -L./libft -lft -L./minilibx-linux -lmlx -lX11 -lXext -lm -o $(NAME); \
	else \
		echo "$(NAME) is up to date"; \
	fi

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)

$(MINI_LIBX):
	$(MAKE) -C $(MINI_LIBX_DIR)

$(OBJ_DIR)%.o: $(SRC)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	make clean -C $(LIB_DIR)
	make clean -C $(MINI_LIBX_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIB_DIR)

re: fclean all

.PHONY: all clean fclean re
