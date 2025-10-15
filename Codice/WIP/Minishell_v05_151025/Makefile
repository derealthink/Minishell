# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/09 13:19:32 by aielo             #+#    #+#              #
#    Updated: 2025/10/15 15:54:46 by aielo            ###   ########.fr        #
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
ENV_DIR		= src/environment
EXEC_DIR 	= src/execution
PARS_DIR 	= src/parsing
SIGN_DIR	= src/signals
UTILS_DIR 	= src/utils

# Sources
BUILT_SRCS 	= $(BUILT_DIR)/builtin_manager.c \
				$(BUILT_DIR)/ft_cd.c \
				$(BUILT_DIR)/ft_echo.c \
				$(BUILT_DIR)/ft_env.c \
				$(BUILT_DIR)/ft_exit.c \
				$(BUILT_DIR)/ft_exit_utils.c \
				$(BUILT_DIR)/ft_export.c \
				$(BUILT_DIR)/ft_export_sort.c \
				$(BUILT_DIR)/ft_export_utils.c \
				$(BUILT_DIR)/ft_pwd.c \
				$(BUILT_DIR)/ft_unset.c

ENV_SRCS 	= $(ENV_DIR)/create_env_list.c \
				$(ENV_DIR)/create_env_array.c

EXEC_SRCS 	= $(EXEC_DIR)/execute_command.c \
				$(EXEC_DIR)/path.c \
				$(EXEC_DIR)/pipeline.c \
				$(EXEC_DIR)/pipeline_utils_one.c \
				$(EXEC_DIR)/pipeline_utils_two.c \
				$(EXEC_DIR)/redirections.c

PARS_SRCS 	= $(PARS_DIR)/lexing.c \
				$(PARS_DIR)/lex_utils.c \
				$(PARS_DIR)/parsing.c \
				$(PARS_DIR)/parsing_utils.c

SIGN_SRCS 	= $(SIGN_DIR)/signals.c

UTILS_SRCS 	= $(UTILS_DIR)/print_logo.c \
				$(UTILS_DIR)/print_error.c \
				$(UTILS_DIR)/ft_utils.c \
				$(UTILS_DIR)/free.c 

SOURCES 	= minishell.c \
				$(BUILT_SRCS) \
				$(ENV_SRCS) \
				$(EXEC_SRCS) \
				$(PARS_SRCS) \
				$(SIGN_SRCS) \
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

$(NAME): | libft $(OBJECTS)
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
