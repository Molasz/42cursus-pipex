# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/07 11:16:50 by molasz-a          #+#    #+#              #
#    Updated: 2024/03/09 17:13:59 by molasz-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= pipex.c \
			childs.c \
			utils.c

BSRCS	= pipex_bonus.c

OPATH	= obj/

OBJS	= ${addprefix ${OPATH}, ${SRCS:.c=.o}}

BOBJS	= ${addprefix ${OPATH}, ${BSRCS:.c=.o}}

DEPS	= ${addprefix ${OPATH}, ${SRCS:.c=.d}}

BDEPS	= ${addprefix ${OPATH}, ${BSRCS:.c=.d}}

NAME	= pipex

RM		= rm -rf

CC		= cc

CFLAGS	= -Wall -Wextra -Werror

LIBFT	= libft/libft.a

all:		dir ${NAME}

bonus:
				make BONUS=1 all

dir:
				mkdir -p obj
				make -C libft


ifndef BONUS

obj/%.o:	src/%.c Makefile
				${CC} ${CFLAGS} -c $< -MMD -o $@

${NAME}:	${OBJS} dir
				${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}

else

obj/%.o:	src/%.c Makefile
				${CC} ${CFLAGS} -c $< -MMD -o $@ -D BONUS=1

${NAME}:	${OBJS} ${BOBJS} dir
				${CC} ${CFLAGS} ${OBJS} ${BOBJS} ${LIBFT} -o ${NAME}

endif

clean:
				make -C libft fclean
				${RM} ${OPATH}

fclean:		clean
				${RM} ${NAME}

re:			fclean all

-include ${DEPS} ${BDEPS}

.PHONY:		all clean fclean re bonus
