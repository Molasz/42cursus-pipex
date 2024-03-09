/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:15:29 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/09 17:33:34 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	pipe_call(t_data *data, int cmd, int *input_pid)
{
	int		status;
	pid_t	pid;

	fprintf(stderr, "PIPE\n");
	pid = fork();
	if (pid < 0)
		on_error(data, "Fork pipe", 0);
	if (!pid)
		pipes(data, cmd);
	if (close(data->end[0]) < 0)
		on_error(data, "Close end[0]", 0);
	if (close(data->end[1]) < 0)
		on_error(data, "Close end[1]", 0);
	waitpid(*input_pid, &status, 0);
	waitpid(pid, &status, 0);
	pipe(data->end);
	*input_pid = pid;
}

int	pipex_bonus(t_data *data)
{
	int		end[2];
	int		status;
	pid_t	input_pid;
	pid_t	output_pid;

	data->end = end;
	pipe(end);
	input_pid = fork_call(data, input);
	output_pid = fork_call(data, output);
	if (close(data->end[0]) < 0)
		on_error(data, "Close end[0]", 0);
	if (close(data->end[1]) < 0)
		on_error(data, "Close end[1]", 0);
	waitpid(input_pid, &status, 0);
	waitpid(output_pid, &status, 0);
	free_all(data);
	return (status);
}
