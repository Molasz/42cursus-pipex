/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:15:29 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/11 16:06:30 by molasz-a         ###   ########.fr       */
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

static void	pipe_end(t_data *data, int i, pid_t *pid, int n)
{
	if (!n)
	{
		fprintf(stderr, "PIPE->PIPE2\n");
		pipe(data->end2);
		*pid = pipe_call(data, pipe_pipe2_child, i + 2);
		if (close(data->end[1]) < 0)
			on_error(data, "Parent pipe close end[1]", 0);
	}
	else
	{
		fprintf(stderr, "PIPE2->PIPE\n");
		pipe(data->end);
		*pid = pipe_call(data, pipe2_pipe_child, i + 2);
		if (close(data->end2[1]) < 0)
			on_error(data, "Parent pipe close end2[1]", 0);
	}
}

static void	pipe_forks(t_data *data)
{
	int		end2[2];
	int		status;
	pid_t	pid;
	int		i;

	data->end2 = end2;
	i = 0;
	while (i < data->argc - 4)
	{
		pipe_end(data, i, &pid, i % 2);
		waitpid(pid, &status, 0);
		i++;
	}
	if (i % 2)
	{
		if (close(data->end[0]) < 0)
			on_error(data, "Pipe on end close end[0]", 0);
	}
}

int	pipex_bonus(t_data *data)
{
	int		status[2];
	pid_t	pids[2];

	pipe(data->end);
	pids[0] = fork_call(data, input_child);
	waitpid(pids[0], &status[0], 0);
	pipe_forks(data);
	pids[1] = pipe_call(data, output_child_bonus, data->argc % 2);
	if (data->argc % 2)
	{
		if (close(data->end2[1]) < 0)
			on_error(data, "Parent end close end2[1]", 0);
		/*
		if (close(data->end2[0]) < 0)
			on_error(data, "Parent end close end2[0]", 0);
			*/
	}
	else
	{
		if (close(data->end[1]) < 0)
			on_error(data, "Parent end close end[1]", 0);
		if (close(data->end[0]) < 0)
			on_error(data, "Parent end close end[0]", 0);
	}
	waitpid(pids[1], &status[1], 0);
	free_all(data);
	return (status[1]);
}

#endif
