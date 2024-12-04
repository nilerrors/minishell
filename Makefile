# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: senayat <senayat@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 22:45:48 by senayat           #+#    #+#              #
#    Updated: 2024/09/23 17:21:48 by senayat          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	./src/minishell.c ./src/handle_line.c

OBJS		=	$(SRCS:.c=.o)

LIB			=	./libft/libft.a

CC			=	gcc
RM			=	rm -f
CFLAGS		=	-Wall -Wextra -Werror

NAME		=	minishell

all:		$(NAME)

%.o:		%.c
			@printf "Making object files\n"
			$(CC) -Wall -Wextra -Werror -c $< -o $@

$(LIB):
			@printf "Making libs\n"
			@$(MAKE) -s -C ./libft

$(NAME):	$(OBJS) $(LIB)
			@printf "Compiling program\n"
			@${CC} ${CFLAGS} ${OBJS} $(LIB) -o ${NAME} -lreadline

clean:
			@$(MAKE) clean -C ./libft
			@$(RM) $(OBJS)

fclean:		clean
			@$(MAKE) fclean -C ./libft
			@$(RM) $(NAME)

re:			fclean	all

.PHONY:		all	clean	fclean	re

