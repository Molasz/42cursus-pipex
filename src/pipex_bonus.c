/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:15:29 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/11 00:37:14 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#ifdef BONUS

static pid_t	pipe_call(t_data *data, void (*f)(t_data *, int), int cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		on_error(data, "Fork pipe", 0);
	if (!pid)
		f(data, cmd);
	return (pid);
}

static void	pipe_forks(t_data *data)
{
	int		end2[2];
	int		status[2];
	pid_t	pids[2];
	int		i;

	data->end2 = end2;
	pipe(end2);
	i = 0;
	while (i < data->argc - 4)
	{
		pids[0] = pipe_call(data, pipe_pipe2_child, i + 2);
		if (i + 1 >= data->argc - 4)
		{
			dup2(data->end[1], data->end2[0]);
			break ;
		}
		pids[1] = pipe_call(data, pipe_pipe2_child, i + 3);
		if (close(data->end2[0]) < 0)
			on_error(data, "Parent pipe close end2[0]", 0);
		if (close(data->end2[1]) < 0)
			on_error(data, "Parent pipe close end2[1]", 0);
		waitpid(pids[0], &status[0], 0);
		waitpid(pids[1], &status[1], 0);
		fprintf(stderr, "0:%d 1:%d\n", status[0], status[1]);
		i += 2;
	}
	if (close(data->end2[0]) < 0)
		on_error(data, "Parent pipe close end2[0]", 0);
	if (close(data->end2[1]) < 0)
		on_error(data, "Parent pipe close end2[1]", 0);
}

int	pipex_bonus(t_data *data)
{
	int		status[2];
	pid_t	pids[2];

	pipe(data->end);
	pids[0] = fork_call(data, input_child);
	pipe_forks(data);
	pids[1] = fork_call(data, output_child);
	if (close(data->end[0]) < 0)
		on_error(data, "Close end[0]", 0);
	if (close(data->end[1]) < 0)
		on_error(data, "Close end[1]", 0);
	waitpid(pids[1], &status[1], 0);
	free_all(data);
	return (status[1]);
}

#endif
