# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/07 11:35:53 by molasz-a          #+#    #+#              #
#    Updated: 2024/03/07 17:10:15 by molasz-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ft_strlen.c \
			ft_strncmp.c \
			ft_split.c \
			ft_split_path.c

OBJS	= ${SRCS:.c=.o}

DEPS	= ${SRCS:.c=.d}

NAME	= libft.a

AR		= ar rcs

RM		= rm -rf

CC		= cc

CFLAGS	= -Wall -Wextra -Werror

all:		${NAME}

%.o:		%.c
				${CC} ${CFLAGS} -c $< -MMD

${NAME}:	${OBJS} Makefile
				${AR} ${NAME} ${OBJS}

clean:
				${RM} ${OBJS} ${DEPS}

fclean:		clean
				${RM} ${NAME}

re:			fclean all

-include ${DEPS}

.PHONY:		all clean fclean re
