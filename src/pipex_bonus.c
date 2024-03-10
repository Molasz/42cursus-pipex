/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:15:29 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/09 19:09:14 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	pipe_input(t_data *data, int *input_pid)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		on_error(data, "Fork pipe", 0);
	if (!pid)
		pipes_input(data);
	if (close(data->end[0]) < 0)
		on_error(data, "Close end[0]", 0);
	if (close(data->end[1]) < 0)
		on_error(data, "Close end[1]", 0);
	waitpid(*input_pid, &status, 0);
	waitpid(pid, &status, 0);
}

static void	pipe_output(t_data *data, int *output_pid)
{
	int		end2[2];
	int		status;
	pid_t	pid;

	data->end2 = end2;
	pipe(end2);
	pid = fork();
	if (pid < 0)
		on_error(data, "Fork pipe", 0);
	if (!pid)
		pipes_output(data);
	if (close(data->end[0]) < 0)
		on_error(data, "Close end[0]", 0);
	if (close(data->end[1]) < 0)
		on_error(data, "Close end[1]", 0);
	waitpid(pid, &status, 0);
	waitpid(*output_pid, &status, 0);
}

static void	pipe_forks(t_data *data, int *end, int *status, pid_t *pids)
{
	int		pend[2];
	pid_t	pid;
	

int	pipex_bonus(t_data *data)
{
	int		end[2];
	int		status[2];
	pid_t	pids[2];

	data->end = end;
	pipe(end);
	pids[0] = fork_call(data, input);
	pipe_forks(data, end, status, pids);
	pids[1] = fork_call(data, output);
	if (close(data->end[0]) < 0)
		on_error(data, "Close end[0]", 0);
	if (close(data->end[1]) < 0)
		on_error(data, "Close end[1]", 0);
	waitpid(pids[0], &status[0], 0);
	waitpid(pids[1], &status[1], 0);
	free_all(data);
	return (status[1]);
}
