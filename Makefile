# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: senayat <senayat@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 22:45:48 by senayat           #+#    #+#              #
#    Updated: 2024/11/03 13:20:29 by senayat          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	./src/minishell.c							\
				./src/signals.c								\
				./src/handle_line.c							\
				./src/tokenize/tokenize.c					\
				./src/tokenize/feed.c						\
				./src/interpolation/interpolation.c			\
				./src/interpolation/str_interpolate_var.c	\
				./src/interpolation/str_interpolation.c		\
				./src/interpolation/take_variablename.c		\
				./src/env/env.c								\
				./src/env/init_env_var.c					\
				./src/env/deinit_env_var.c					\
				./src/env/env_from_envstr.c					\
				./src/env/get_env_var.c						\
				./src/env/is_valid_env_var.c				\
				./src/env/remove_env_var.c					\
				./src/env/set_env_var.c						\
				./src/tokenize/tokenize_help.c				\
				./src/parse/parse.c							\
				./src/parse/parse_help.c					\
				./src/parse/parse_handlers.c				\
				./src/execute/execute.c						\
				./src/execute/execute_act_command.c			\
				./src/execute/execute_act_pipe.c			\
				./src/execute/execute_help.c				\
				./src/execute/execute_utils.c				\
				./src/builtin/builtin.c						\
				./src/builtin/execute_chdir.c				\
				./src/builtin/execute_echo.c				\
				./src/builtin/execute_env.c					\
				./src/builtin/execute_exit.c				\
				./src/builtin/execute_export.c				\
				./src/builtin/execute_pwd.c					\
				./src/builtin/execute_unset.c				\
				./src/redirections/redirections.c			\
				./src/redirections/heredoc.c				\
				./src/redirections/get_heredoc_content.c

OBJS		=	$(SRCS:.c=.o)

LIB			=	./libft/libft.a

CC			=	cc
RM			=	rm -f
CFLAGS		=	-Wall -Wextra -Werror
LFLAGS		=	-lreadline

NAME		=	minishell

all:		$(NAME)


%.o:		%.c
			@printf "Making object file: $@\n"
			@$(CC) -Wall -Wextra -Werror -c -o $@ $<

$(LIB):
			@printf "Making libft\n"
			@$(MAKE) -s -C ./libft

$(NAME):	$(OBJS) $(LIB)
			@printf "Compiling program\n"
			@${CC} ${CFLAGS} ${OBJS} $(LIB) -o ${NAME} ${LFLAGS}

clean:
			@$(MAKE) clean -s -C ./libft
			@$(RM) $(OBJS)

fclean:		clean
			@$(MAKE) fclean -s -C ./libft
			@$(RM) $(NAME)

re:			fclean	all

.PHONY:		all	clean	fclean	re
