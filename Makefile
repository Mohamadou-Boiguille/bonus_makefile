# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/10 12:19:24 by hamzaelouar       #+#    #+#              #
#    Updated: 2023/09/10 19:37:59 by hamzaelouar      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME		= cub3D
# CC			= cc
# CFLAGS		= -Wall -Wextra -Werror -g3
# RM			= rm -rf

# HEADER       = includes/cub3d.h
# HEADER_BONUS = bonus/includes/cub3D.h


# SRC_PATH	= srcs/
# SRCS        =										\
# 			get_next_line/get_next_line.c			\
# 			map/display.c							\
# 			map/map_check_closing.c					\
# 			map/map_data.c							\
# 			map/map.c								\
# 			parser/helpers.c						\
# 			parser/init.c							\
# 			parser/bonus_init.c						\
# 			parser/specific_split.c					\
# 			raycast/movements.c						\
# 			raycast/raycasting.c					\
# 			raycast/raycasting_helpers.c			\
# 			garbage_collector.c						\
# 			keys.c									\
# 			main.c									\

# OBJS_DIR	= .objects/
# OBJS        = $(patsubst %.c, $(OBJS_DIR)%.o, $(SRCS))

# LIBFT_PATH   = libft/
# LIBFT_L      = -L$(LIBFT_PATH) -lft
# LIBFT_L_BONUS= -Lbonus/libft -lft

# MLX = -Lmlx_linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz

# all: make_libft $(NAME)

# $(NAME): $(OBJS) Makefile $(HEADER)
# 	$(CC) $(CFLAGS) -I$(HEADER) $(OBJS) $(MLX) $(LIBFT_L) -o $@

# bonus: make_libft_bonus Makefile
# 	$(CC) $(CFLAGS) -I$(HEADER_BONUS) $(OBJS) $(MLX) $(LIBFT_L_BONUS) -o $@

# $(OBJS_DIR)%.o: $(SRC_PATH)%.c $(LIBFT_A) $(LIBFT_PATH) $(HEADER)
# 	mkdir -p $(dir $@)
# 	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# make_libft:
# 	make -C libft/

# make_libft_bonus:
# 	make -c bonus/libft/

# clean:
# 	$(RM) $(OBJS_DIR)
# 	make clean -C libft/

# fclean: clean
# 	$(RM) $(NAME)
# 	make fclean -C libft/

# re: fclean all

# .PHONY: all clean fclean re make_libft

NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3
RM          = rm -rf

HEADER       = mandatory/includes/cub3d.h
HEADER_BONUS = bonus/includes/cub3d_bonus.h

SRC_PATH    = mandatory/srcs/
SRCS        =                                       \
            get_next_line/get_next_line.c           \
            map/display.c                          \
            map/map_check_closing.c                \
            map/map_data.c                         \
            map/map.c                              \
            parser/helpers.c                       \
            parser/init.c                          \
            parser/specific_split.c                \
            raycast/movements.c                    \
            raycast/raycasting.c                   \
            raycast/raycasting_helpers.c           \
            garbage_collector.c                    \
            keys.c                                  \
            main.c                                  \

SRC_PATH_BONUS    = mandatory/srcs/ 
SRCS_BONUS        =                                       \
            get_next_line/get_next_line_bonus.c           \
            map/display_bonus.c                          \
            map/map_check_closing_bonus.c                \
            map/map_data_bonus.c                         \
            map/map_bonus.c                              \
            parser/helpers_bonus.c                       \
            parser/init_bonus.c                          \
            parser/bonus_init_bonus.c                    \
            parser/specific_split_bonus.c                \
            raycast/movements_bonus.c                    \
            raycast/raycasting_bonus.c                   \
            raycast/raycasting_helpers_bonus.c           \
            garbage_collector_bonus.c                    \
            keys_bonus.c                                  \
            main_bonus.c                                  \

OBJS_DIR    = .objects/
OBJS        = $(patsubst %.c, $(OBJS_DIR)%.o, $(SRCS))
OBJS_BONUS  = $(patsubst $(SRC_PATH_BONUS)%.c,$(OBJS_DIR)%.o,$(SRCS_BONUS))

LIBFT_PATH   = mandatory/libft/
LIBFT_L      = -L$(LIBFT_PATH) -lft
LIBFT_PATH_BONUS   = bonus/libft/
LIBFT_L_BONUS= -L$(LIBFT_PATH_BONUS) -lft

ifeq ($(MAKECMDGOALS),bonus)
	MLX = -Lbonus/mlx_linux -Lbonus/mlx -lmlx -lXext -lX11 -lm -lz
else
	MLX = -Lmandatory/mlx_linux -Lmandatory/mlx -lmlx -lXext -lX11 -lm -lz
# MLX = -Lmandatory/mlx_linux -Lmandatory/mlx -L/usr/lib -lXext -lX11 -lm -lz
endif

all: make_libft $(NAME)

$(NAME): $(OBJS) Makefile $(HEADER)
	$(CC) $(CFLAGS) -I$(HEADER) $(OBJS) $(MLX) $(LIBFT_L) -o mandatory/cub3D

# bonus: make_libft_bonus $(OBJS) Makefile $(HEADER_BONUS)
# 	$(CC) $(CFLAGS) -I$(HEADER_BONUS) $(OBJS) $(MLX) $(LIBFT_L_BONUS) -o $@

bonus: make_libft_bonus $(OBJS_BONUS) Makefile $(HEADER_BONUS)
	$(CC) $(CFLAGS) -I$(HEADER_BONUS) $(OBJS_BONUS) $(MLX) $(LIBFT_L_BONUS) -o bonus/cub3D_bonus

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

# Règle pour construire les fichiers objets pour la version bonus
$(OBJS_DIR)%.o: $(SRC_PATH_BONUS)%.c $(LIBFT_A) $(LIBFT_PATH_BONUS) $(HEADER_BONUS) | $(OBJS_DIR)
	mkdir -p $(dir $@)  # Crée récursivement le répertoire du fichier objet
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# Règle pour construire les fichiers objets pour la version normale
$(OBJS_DIR)%.o: $(SRC_PATH)%.c $(LIBFT_A) $(LIBFT_PATH) $(HEADER) | $(OBJS_DIR)
	mkdir -p $(dir $@)  # Crée récursivement le répertoire du fichier objet
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

make_libft:
	make -C mandatory/libft/

make_libft_bonus:
	make -C bonus/libft/

clean:
	$(RM) $(OBJS_DIR)
	make clean -C mandatory/libft/
	make clean -C bonus/libft/

fclean: clean
	$(RM) $(NAME)
	make fclean -C mandatory/libft/
	make fclean -C bonus/libft/

re: fclean all

.PHONY: all clean fclean re make_libft bonus
