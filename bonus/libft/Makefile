# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/10 12:17:07 by hamzaelouar       #+#    #+#              #
#    Updated: 2023/09/10 12:17:10 by hamzaelouar      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Dossiers
SRC_DIR = src
OBJ_DIR = .obj

# Fichiers source
SRC_FILES = ft_atoi.c ft_lstadd_back.c ft_memcmp.c ft_strchr.c ft_strrchr.c \
            ft_bzero.c ft_lstadd_front.c ft_memcpy.c ft_strdup.c ft_strtrim.c \
            ft_calloc.c ft_lstclear.c ft_memmove.c ft_striteri.c ft_substr.c \
            ft_isalnum.c ft_lstdelone.c ft_memset.c ft_strjoin.c ft_tolower.c \
            ft_isalpha.c ft_lstiter.c ft_putchar_fd.c ft_strlcat.c ft_toupper.c \
            ft_isascii.c ft_lstlast.c ft_putendl_fd.c ft_strlcpy.c \
            ft_isdigit.c ft_lstmap.c ft_putnbr_fd.c ft_strlen.c \
            ft_isprint.c ft_lstnew.c ft_putstr_fd.c ft_strmapi.c \
            ft_isspace.c ft_lstsize.c ft_set_split.c ft_strncmp.c \
            ft_itoa.c ft_memchr.c ft_split.c ft_strnstr.c

# Fichiers objets
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ_PATHS = $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

# Bibliothèque
LIB = libft.a

# Règles de compilation
all: $(LIB)

$(LIB): $(OBJ_PATHS)
	ar rc $@ $^
	ranlib $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(LIB)

re: fclean all

.PHONY: all clean fclean re
