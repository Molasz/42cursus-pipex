/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:15:29 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/11 01:29:22 by molasz-a         ###   ########.fr       */
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
		pipe(data->end2);
		*pid = pipe_call(data, pipe_pipe2_child, i + 2);
		if (close(data->end[0]) < 0)
			on_error(data, "Parent pipe close end2[0]", 0);
		if (close(data->end[1]) < 0)
			on_error(data, "Parent pipe close end2[1]", 0);
	}
	else
	{
		pipe(data->end);
		*pid = pipe_call(data, pipe2_pipe_child, i + 2);
		if (close(data->end2[0]) < 0)
			on_error(data, "Parent pipe close end2[0]", 0);
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
		if (!(i % 2))
			pipe_end(data, i, &pid, 0);
		else
			pipe_end(data, i, &pid, 1);
		waitpid(pid, &status, 0);
		fprintf(stderr, "STATUS:%d [%s]\n", status, data->argv[i + 2]);
		i++;
	}
	if (i % 2)
		data->end = data->end2;

}

int	pipex_bonus(t_data *data)
{
	int		status[2];
	pid_t	pids[2];

	pipe(data->end);
	pids[0] = fork_call(data, input_child);
	waitpid(pids[0], &status[0], 0);
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
