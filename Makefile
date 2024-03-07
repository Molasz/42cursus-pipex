# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/07 11:16:50 by molasz-a          #+#    #+#              #
#    Updated: 2024/03/07 13:55:59 by molasz-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= pipex.c \
			child.c \
			parent.c

OPATH	= obj/

OBJS	= ${addprefix ${OPATH}, ${SRCS:.c=.o}}

DEPS	= ${addprefix ${OPATH}, ${SRCS:.c=.d}}

NAME	= pipex

RM		= rm -rf

CC		= cc

CFLAGS	= -Wall -Wextra -Werror

LIBFT	= libft/libft.a

all:		dir ${NAME}

dir:
				mkdir -p obj
				make -C libft

obj/%.o:	src/%.c Makefile
				${CC} ${CFLAGS} -c $< -MMD -o $@

${NAME}:	${OBJS} dir
				${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}

clean:
				${RM} ${OPATH}

fclean:		clean
				make -C fclean libft

re:			fclean all

-include ${DEPS}

.PHONY:		all clean fclean re
