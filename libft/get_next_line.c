/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:39:30 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/12 00:41:52 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_buffer(t_file *file)
{
	char	*str;
	int		read_len;

	str = malloc(BUFFER_SIZE + 1);
	if (!str)
		return (1);
	read_len = read(file->fd, str, BUFFER_SIZE);
	if (read_len < 0)
	{
		free_end(str, NULL, file);
		return (1);
	}
	else if (read_len > 0)
	{
		if (read_len < BUFFER_SIZE)
			file->end = 1;
		str[read_len] = '\0';
		str = gl_strjoin(file->buff, str);
		if (!str)
			return (1);
		file->buff = str;
	}
	else
		free_end(str, NULL, file);
	return (0);
}

static int	newline_buff(t_file *file)
{
	int	i;

	if (!file->buff)
		return (0);
	i = 0;
	while (file->buff[i])
	{
		if (file->buff[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static int	calc_buff(t_file *file, char *line)
{
	char	*res;
	int		line_len;
	int		i;

	res = NULL;
	line_len = gl_strlen(line);
	if (line_len)
	{
		res = malloc(gl_strlen(file->buff) - line_len + 1);
		if (!res)
			return (1);
		i = 0;
		while (file->buff[i + line_len])
		{
			res[i] = file->buff[i + line_len];
			i++;
		}
		res[i] = '\0';
	}
	free(file->buff);
	file->buff = res;
	return (0);
}

static char	*buff_next_line(t_file *file)
{
	char	*line;

	while (!newline_buff(file) && !file->end)
	{
		if (read_buffer(file))
			return (NULL);
	}
	if (file->end && !file->buff)
		return (NULL);
	line = new_line(file);
	if (calc_buff(file, line))
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static t_file	files[10];
	t_file			*file;
	char			*next_line;

	if (fd < 0 || fd > 10)
		return (NULL);
	file = get_file(files, fd);
	next_line = buff_next_line(file);
	if (!next_line)
	{
		if (file->buff)
			free(file->buff);
		file->init = 0;
	}
	return (next_line);
}
