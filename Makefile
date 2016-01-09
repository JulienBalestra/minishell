# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/02/20 11:34:39 by jubalest          #+#    #+#              #
#    Updated: 2015/03/11 12:50:57 by jubalest         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libsh
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
INC_DIR = includes/
SRC_DIR = srcs/
OBJ_DIR = .objects/
OBJS = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
TARGET = $(NAME).a
BIN = minishell
ENV = $(shell uname -s)


CL_CYAN = \033[0;36m
CL_GREED = \033[0;32m
CL_RED = \033[0;31m
CL_WHITE = \033[0m


SRC =               \
input_format.c  \
misc_string.c	\
manage_path.c \
build_props.c \
cleaner.c \
misc_prompt.c \
builtin_env.c \
builtin_unsetenv.c \
manage_builtins.c\
manage_interpretor.c\
update_last_environ.c \
builtin_exit.c \
builtin_setenv.c \
builtin_getenv.c \
builtin_cd.c \
empty_extern_environ.c \
misc_parse_env.c \
parse_env.c \
env_errors.c \
display_env.c \
run_under_env.c \
manage_link.c \
merge_environ.c \
misc_interpretor.c \
misc_read.c \
reader.c \
cd_goto.c \
syntax.c \
misc_cd.c \
manage_fork.c \
format_path.c \
cd_opt.c \
misc_prompt2.c \
cd_is_valid.c \
misc_cd2.c \
chdir_var.c \
cd_symbolic.c \
\
21ast_build.c \
21ast_clean.c \
21ast_read.c \
21ast_exec.c


MAIN = srcs/main.c


.PHONY: all clean fclean re

default: all

all: $(NAME)
	@echo " # sh : Job done  $(shell pwd)/$(CL_GREED)$(TARGET)$(CL_WHITE)"
	@echo " # sh : Job done  $(shell pwd)/$(CL_GREED)$(BIN)$(CL_WHITE)"

$(NAME): $(OBJ_DIR) $(TARGET)

$(TARGET): $(OBJS)
	@make -C libft/ -j -s
	@echo " + sh : Creating  $(CL_GREED)$@$(CL_WHITE) $(shell sleep 0.01)"
	@ar -rcv $(TARGET) $(OBJS) > /dev/null
	@ranlib $(TARGET)
	@$(CC) $(CFLAGS) srcs/main.c $(TARGET) libft/libft.a -I $(INC_DIR) -I libft/includes  -o $(BIN)

clean:
	@echo " $(shell\
				if [ -d $(OBJ_DIR) ];\
				then\
					echo "- sh : Removing $(CL_RED)$(OBJ_DIR)$(CL_WHITE) with$(CL_RED)";\
					ls $(OBJ_DIR) | wc -w; echo "$(CL_WHITE)*.o";\
					rm -Rf $(OBJ_DIR);\
				else\
					echo "# sh : Nothing to clean";\
				fi)"
	@make -C libft/ clean -s


fclean: clean
	@echo " $(shell\
					if [ -f libft/libft.a ];\
						then\
							echo "- ft : Removing  $(CL_RED)$ libft.a $(CL_WHITE)";\
							rm -f libft/libft.a;\
					else\
							echo "";\
					fi)"
	@echo " $(shell\
					if [ -f $(TARGET) ];\
					then\
						echo "- sh : Removing  $(CL_RED)$(TARGET)$(CL_WHITE)";\
						rm -f $(TARGET);\
					else\
						echo "# sh : Nothing to fclean";\
					fi)"
	@echo " $(shell\
					if [ -f $(BIN) ];\
						then\
							echo "- sh : Removing  $(CL_RED)$ $(BIN) $(CL_WHITE)";\
							rm -f $(BIN);\
					else\
							echo "# ft : Nothing to fclean";\
					fi)"

re: fclean all

$(addprefix $(OBJ_DIR), %.o): $(addprefix $(SRC_DIR), %.c)
	@echo " + sh : Compiling $(CL_CYAN)$(OBJ_DIR) < $^$(CL_WHITE)"
	@$(CC) $(CFLAGS) -I $(INC_DIR) -I libft/includes -o $@ -c $<

$(OBJ_DIR):
	@echo " # sh : $(ENV) kernel"
	@echo " + sh : Creating $(CL_GREED)$(OBJ_DIR)$(CL_WHITE)$(CL_WHITE)"
	@mkdir -p $(OBJ_DIR)

