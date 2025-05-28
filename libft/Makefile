# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/10 15:58:19 by douzgane          #+#    #+#              #
#    Updated: 2024/08/10 16:05:33 by douzgane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a

LIBFT_DIR = libft/
PRINTF_DIR = ft_printf/
GNL_DIR = get_next_line/


LIBFT_SRCS = $(wildcard $(LIBFT_DIR)*.c)
PRINTF_SRCS = $(wildcard $(PRINTF_DIR)*.c)
GNL_SRCS = $(wildcard $(GNL_DIR)*.c)

SRCS = $(LIBFT_SRCS) $(PRINTF_SRCS) $(GNL_SRCS)
OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -g -Wall -Wextra -Werror
AR = ar rcs

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
