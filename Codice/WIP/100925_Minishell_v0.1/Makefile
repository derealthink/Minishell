# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aielo <aielo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/09 13:19:32 by aielo             #+#    #+#              #
#    Updated: 2025/09/10 14:49:57 by aielo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIB_DIR = Libft
LIB_NAME = ft
LIB_LIB = $(LIB_DIR)/lib$(LIB_NAME).a
LIB_INC = $(LIB_DIR)

PRINT_DIR = Ft_Printf
PRINT_NAME = ftprintf
PRINT_LIB = $(PRINT_DIR)/lib$(PRINT_NAME).a
PRINT_INC = $(PRINT_DIR)

SRC_DIR = src

SOURCES = minishell.c \
		$(SRC_DIR)/print_logo.c

OBJECTS = $(SOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
CEXTRA_INC = -I. -I$(LIB_INC) -I$(PRINT_INC)
CEXTRA_LIB = -L$(LIB_DIR) -l$(LIB_NAME) -L$(PRINT_DIR) -l$(PRINT_NAME)

all: libft libftprintf $(NAME)

bonus: libft libftprintf $(NAME)

$(NAME):  $(LIB_LIB) $(PRINT_LIB) $(OBJECTS)
	@echo "\033[32m----Compiling $(NAME)----"
	@echo "\033[0m"
	$(CC) $(CFLAGS) $(CEXTRA_INC) $(OBJECTS) -o $(NAME) $(CEXTRA_LIB)
	@echo "\033[32m----$(NAME) compiled!----"
	@echo "\033[0m"

libft:
	@echo "\033[32m----Compiling libft----"
	@echo "\033[0m"
	$(MAKE) -C $(LIB_DIR)
	@echo "\033[32m----Libft compiled!----"
	@echo "\033[0m"

libftprintf:
	@echo "\033[32m----Compiling printf----"
	@echo "\033[0m"
	$(MAKE) -C $(PRINT_DIR)
	@echo "\033[32m----Printf compiled!----"
	@echo "\033[0m"

%.o: %.c
	$(CC) $(CFLAGS) $(CEXTRA_INC) -c $< -o $@

clean:
	rm -f $(OBJECTS)
	$(MAKE) -C $(LIB_DIR) clean
	$(MAKE) -C $(PRINT_DIR) clean

fclean: clean
	@echo "\n\033[31m----Deleting EVERYTHING!----\n"
	@echo "\033[0m"
	rm -f $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean
	$(MAKE) -C $(PRINT_DIR) fclean
	@echo "\n\033[31m----EVERYTHING deleted!----\n"
	@echo "\033[0m"

re: fclean all

val:	re
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./$(NAME)

.PHONY: all bonus clean fclean re libft libftprintf
