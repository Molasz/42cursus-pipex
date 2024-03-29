# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/07 11:16:50 by molasz-a          #+#    #+#              #
#    Updated: 2024/03/17 14:53:52 by molasz-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= pipex.c \
			utils.c \
			utils_bonus.c

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
				make -C libft fclean
				${RM} ${OPATH}

fclean:		clean
				${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
