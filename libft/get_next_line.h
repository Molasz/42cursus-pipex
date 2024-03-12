/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:40:36 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/12 00:41:42 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_file
{
	int		fd;
	int		init;
	int		end;
	char	*buff;
}		t_file;

char	*get_next_line(int fd);

t_file	*get_file(t_file *files, int fd);
size_t	gl_strlen(char *s);
char	*gl_strjoin(char *s1, char *s2);
char	*new_line(t_file *file);
void	free_end(char *s1, char *s2, t_file *file);

#endif
