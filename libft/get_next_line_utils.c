/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:40:24 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/12 00:42:30 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_file	*get_file(t_file *files, int fd)
{
	t_file	*file;

	file = files + fd;
	if (!file->init)
	{
		file->fd = fd;
		file->end = 0;
		file->init = 1;
		file->buff = NULL;
		files[fd] = *file;
	}
	return (file);
}

size_t	gl_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*gl_strjoin(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	res = malloc((gl_strlen(s1) + gl_strlen(s2) + 1));
	if (!res)
	{
		free(s2);
		return (NULL);
	}
	i = 0;
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	free_end(s1, s2, NULL);
	res[i + j] = '\0';
	return (res);
}

char	*new_line(t_file *file)
{
	char	*line;
	int		len;
	int		i;

	len = 0;
	while (file->buff[len] != '\n' && file->buff[len] != '\0')
		len++;
	if (file->buff[len] == '\n')
		len++;
	if (!len)
		return (NULL);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	line[len] = '\0';
	i = 0;
	while (i < len)
	{
		line[i] = file->buff[i];
		i++;
	}
	return (line);
}

void	free_end(char *s1, char *s2, t_file *file)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (file)
		file->end = 1;
}
