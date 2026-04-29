# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/09 13:19:32 by aielo             #+#    #+#              #
#    Updated: 2026/04/29 19:32:12 by aielo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		:= minishell

# Bash
GREEN		:= \033[0;32m
RESET		:= \033[0m
RM			:= rm -rf
MKDIR		:= mkdir -p

# Libraries
LIBFT_DIR	:= libft
LIBFT_A		:= $(LIBFT_DIR)/libft.a
LIBFT_H		:= $(LIBFT_DIR)/includes

# Directories
INC_DIR		:= includes
OBJ_DIR 	:= obj

BUILT_DIR 	:= src/builtins
ENV_DIR		:= src/environment
EXEC_DIR 	:= src/execution
MAIN_DIR 	:= src/main
PARS_DIR 	:= src/parsing
CONFIG_DIR	:= src/configuration
UTILS_DIR 	:= src/utils

# Sources
BUILT_SRCS 	:= $(BUILT_DIR)/builtin_manager.c \
				$(BUILT_DIR)/ft_cd.c \
				$(BUILT_DIR)/ft_cd_utils.c \
				$(BUILT_DIR)/ft_echo.c \
				$(BUILT_DIR)/ft_env.c \
				$(BUILT_DIR)/ft_exit.c \
				$(BUILT_DIR)/ft_exit_utils.c \
				$(BUILT_DIR)/ft_export.c \
				$(BUILT_DIR)/ft_export_sort.c \
				$(BUILT_DIR)/ft_export_utils.c \
				$(BUILT_DIR)/ft_pwd.c \
				$(BUILT_DIR)/ft_unset.c

ENV_SRCS 	:= $(ENV_DIR)/create_env_list.c \
				$(ENV_DIR)/create_env_list_utils.c \
				$(ENV_DIR)/create_env_array.c \
				$(ENV_DIR)/shell_level.c \
				$(ENV_DIR)/expand_var.c \
				$(ENV_DIR)/expand_var_utils.c

EXEC_SRCS 	:= $(EXEC_DIR)/execute_command.c \
				$(EXEC_DIR)/path.c \
				$(EXEC_DIR)/pipeline.c \
				$(EXEC_DIR)/pipeline_command.c \
				$(EXEC_DIR)/pipeline_utils_one.c \
				$(EXEC_DIR)/pipeline_utils_two.c \
				$(EXEC_DIR)/redirections.c

MAIN_SRCS	:= $(MAIN_DIR)/init.c \
				$(MAIN_DIR)/main_loop.c

PARS_SRCS 	:= $(PARS_DIR)/lexing.c \
				$(PARS_DIR)/lex_utils.c \
				$(PARS_DIR)/parsing.c \
				$(PARS_DIR)/parsing_utils.c \
				$(PARS_DIR)/parse_errors.c \
				$(PARS_DIR)/parse_errors_utils.c \
				$(PARS_DIR)/lex_utils_1.c \
				$(PARS_DIR)/parsing_utils_1.c \
				$(PARS_DIR)/parsing_utils_2.c

CONFIG_SRCS	:= $(CONFIG_DIR)/signals.c \
				$(CONFIG_DIR)/signals_heredoc.c \
				$(CONFIG_DIR)/terminal_config.c

UTILS_SRCS 	:= $(UTILS_DIR)/print_logo.c \
				$(UTILS_DIR)/print_error.c \
				$(UTILS_DIR)/ft_utils.c \
				$(UTILS_DIR)/free.c 

SRCS	 	:= minishell.c \
				$(BUILT_SRCS) \
				$(ENV_SRCS) \
				$(EXEC_SRCS) \
				$(MAIN_SRCS) \
				$(PARS_SRCS) \
				$(CONFIG_SRCS) \
				$(UTILS_SRCS)

# Objects
OBJ		 	:= $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Compiler
CC 			:= cc
CFLAGS 		:= -Wall -Wextra -Werror -MMD -MP
CPPFLAGS	:= -I. -I$(INC_DIR) -I$(LIBFT_H)
LDFLAGS 	:= -L$(LIBFT_DIR)
LDLIBS		:= -lreadline

# Dependency
DEPENDS 	:= $(OBJ:.o=.d)

# Rules
all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) $(LDLIBS) $(LIBFT_A) -o $@
	@echo "$(GREEN) $(NAME) compiled!$(RESET)"

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: %.c
	@$(MKDIR) $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

-include $(DEPENDS)

clean:
	@$(RM) $(OBJ_DIR)
	@echo "$(GREEN) Object files removed.$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@echo "$(GREEN) $(NAME) removed.$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) fclean

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
		./$(NAME)

valre: re val

.PHONY: all clean fclean re libft debug val valre
