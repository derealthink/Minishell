# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aielo <aielo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/09 13:19:32 by aielo             #+#    #+#              #
#    Updated: 2025/09/29 18:18:24 by aielo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell

# Libraries
LIB_DIR 	= libft
LIB_NAME 	= ft
LIB_LIB 	= $(LIB_DIR)/lib$(LIB_NAME).a
LIB_INC 	= $(LIB_DIR)

# Directories
INCLUDES 	= includes
OBJ_DIR 	= obj

BUILT_DIR 	= src/builtins
EXEC_DIR 	= src/execution
PARS_DIR 	= src/parsing
UTILS_DIR 	= src/utils

# Sources
BUILT_SRCS 	= $(BUILT_DIR)/builtin_manager.c \
				$(BUILT_DIR)/directories.c \
				$(BUILT_DIR)/enviroment.c

EXEC_SRCS 	= $(EXEC_DIR)/exec_command.c \
				$(EXEC_DIR)/path.c \
				$(EXEC_DIR)/pipeline.c \
				$(EXEC_DIR)/redirections.c \

PARS_SRCS 	= $(PARS_DIR)/lex_utils.c \
				$(PARS_DIR)/lexing.c \
				$(PARS_DIR)/parsing.c \
				$(PARS_DIR)/parsing_utils.c \

UTILS_SRCS 	= $(UTILS_DIR)/print_logo.c \
				$(UTILS_DIR)/free.c \
				$(UTILS_DIR)/signal.c

SOURCES 	= minishell.c \
				$(BUILT_SRCS) \
				$(EXEC_SRCS) \
				$(PARS_SRCS) \
				$(UTILS_SRCS)

# Objects
OBJECTS 	= $(SOURCES:%.c=$(OBJ_DIR)/%.o)

# Compiler
CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror
CEXTRA_INC 	= -I. -I$(LIB_INC) -I$(INCLUDES)
CEXTRA_LIB 	= -L$(LIB_DIR) -l$(LIB_NAME) -lreadline

# Dependency
DEPENDS 	= $(OBJECTS:.o=.d)

# Rules
all: $(OBJ_DIR) libft $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(LIB_LIB) $(OBJECTS)
	$(CC) $(CFLAGS) $(CEXTRA_INC) $(OBJECTS) -o $(NAME) $(CEXTRA_LIB)

libft:
	$(MAKE) -C $(LIB_DIR)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CEXTRA_INC) -MMD -MP -c $< -o $@

-include $(DEPENDS)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

# Debug rules
debug: CFLAGS += -g3 -fsanitize=address
debug: re

# Valgrind rules
val: $(NAME)
	valgrind \
		--leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		--suppressions=supp.supp \
		./$(NAME)

valre: re val

.PHONY: all clean fclean re libft debug val valre
