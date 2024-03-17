/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:34:37 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/17 15:32:17 by molasz-a         ###   ########.fr       */
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

static char	*get_limiter(t_data *data)
{
	char	*limiter;

	limiter = ft_strjoin(data->argv[0], "\n");
	if (!limiter)
		on_error(data, "Limiter join", 0);
	write(1, "pipe heredoc> ", 14);
	return (limiter);
}

void	here_doc(t_data *data)
{
	char	*line;
	char	*limiter;

	if (pipe(data->end))
		on_error(data, "Pipe", 0);
	limiter = get_limiter(data);
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			continue ;
		if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
			break ;
		write(1, "pipe heredoc> ", 14);
		write(data->end[1], line, ft_strlen(line));
		free(line);
	}
	free(limiter);
	if (dup2(data->end[0], 0) < 0)
		on_error(data, "Here_doc dup end[0]", 0);
	if (close(data->end[0]) < 0)
		on_error(data, "Here_doc close end[0]", 0);
	if (close(data->end[1]) < 0)
		on_error(data, "Here_doc close end[1]", 0);
	free(line);
}
