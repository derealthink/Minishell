# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/24 12:29:39 by aielo             #+#    #+#              #
#    Updated: 2025/06/27 23:38:30 by aielo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC_DIR = srcs
UTL_DIR = utils

CC = cc
CFLAGS = -Wall -Wextra -Werror
CEXTRA = -I.

SOURCES = ft_printf.c \
	$(SRC_DIR)/ft_printf_c.c $(SRC_DIR)/ft_printf_di.c \
	$(SRC_DIR)/ft_printf_s.c $(SRC_DIR)/ft_printf_u.c \
	$(SRC_DIR)/ft_printf_x.c $(SRC_DIR)/ft_printf_p.c \
	$(SRC_DIR)/ft_printf_per.c \
	$(SRC_DIR)/ft_flags.c $(SRC_DIR)/ft_flag_width.c \
	$(SRC_DIR)/ft_flag_precision.c \
	$(UTL_DIR)/ft_itoa.c $(UTL_DIR)/ft_itoa_u.c $(UTL_DIR)/ft_itoa_x.c \
	$(UTL_DIR)/ft_itoa_p.c $(UTL_DIR)/ft_putchar_fd.c $(UTL_DIR)/ft_putstr_fd.c \
	$(UTL_DIR)/ft_strlen.c $(UTL_DIR)/ft_substr.c $(UTL_DIR)/ft_isdigit.c \
	$(UTL_DIR)/ft_atoi.c \

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(CEXTRA) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
