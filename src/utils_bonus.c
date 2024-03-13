/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:34:37 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/13 16:23:48 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	fork_bonus(t_data *data, int cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		on_error(data, "Fork pipe", 0);
	if (!pid)
	{
		if (dup2(data->end[1], 1) < 0)
			on_error(data, "Child dup end[1]", 0);
		if (close(data->end[0]) < 0)
			on_error(data, "Child close end[0]", 0);
		run_cmd(data, data->argv[cmd]);
	}
	if (dup2(data->end[0], 0) < 0)
		on_error(data, "Parent dup end[0]", 0);
	if (close(data->end[1]) < 0)
		on_error(data, "Parent close end[1]", 0);
}

void	here_doc(t_data *data)
{
	char	*line;

	pipe(data->end);
	write(1, "pipe heredoc> ", 14);
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			continue ;
		if (!ft_strncmp(line, data->argv[0], ft_strlen(data->argv[0])))
			break ;
		write(1, "pipe heredoc> ", 14);
		write(data->end[1], line, ft_strlen(line));
		free(line);
	}
	if (dup2(data->end[0], 0) < 0)
		on_error(data, "Here_doc dup end[0]", 0);
	if (close(data->end[0]) < 0)
		on_error(data, "Here_doc close end[0]", 0);
	if (close(data->end[1]) < 0)
		on_error(data, "Here_doc close end[1]", 0);
	free(line);
}
