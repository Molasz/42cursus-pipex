/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:16:05 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/11 19:10:41 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	input_child(t_data *data)
{
	if (dup2(data->infile, 0) < 0)
		on_error(data, "Input dup infile", 0);
	if (dup2(data->end[1], 1) < 0)
		on_error(data, "Input dup end[1]", 0);
	if (close(data->end[0]) < 0)
		on_error(data, "Input close end[0]", 0);
	if (close(data->infile) < 0)
		on_error(data, "Input close infile", 0);
	run_cmd(data, data->argv[1]);
}

void	output_child(t_data *data)
{
	if (dup2(data->outfile, 1) < 0)
		on_error(data, "Output dup outfile", 0);
	if (dup2(data->end[0], 0) < 0)
		on_error(data, "Output dup end[0]", 0);
	if (close(data->end[1]) < 0)
		on_error(data, "Output close end[1]", 0);
	if (close(data->outfile) < 0)
		on_error(data, "Output close outfile", 0);
	run_cmd(data, data->argv[data->argc - 2]);
}

#ifdef BONUS

void	pipe_pipe2_child(t_data *data, int cmd)
{
	if (dup2(data->end[0], 0) < 0)
		on_error(data, "Child pipe->pipe2 dup end[0]", 0);
	if (dup2(data->end2[1], 1) < 0)
		on_error(data, "Child pipe->pipe2 dup end2[1]", 0);
	if (close(data->end[1]) < 0)
		on_error(data, "Child pipe->pipe2 close end[1]", 0);
	if (close(data->end2[0]) < 0)
		on_error(data, "Child pipe->pipe2 close end2[0]", 0);
	run_cmd(data, data->argv[cmd]);
}

void	pipe2_pipe_child(t_data *data, int cmd)
{
	if (dup2(data->end2[0], 0) < 0)
		on_error(data, "Child pipe2->pipe dup end2[0]", 0);
	if (dup2(data->end[1], 1) < 0)
		on_error(data, "Child pipe2->pipe dup end[1]", 0);
	if (close(data->end2[1]) < 0)
		on_error(data, "Child pipe2->pipe close end2[1]", 0);
	if (close(data->end[0]) < 0)
		on_error(data, "Child pipe2->pipe close end[0]", 0);
	run_cmd(data, data->argv[cmd]);
}

void	output_child_bonus(t_data *data, int n)
{
	if (dup2(data->outfile, 1) < 0)
		on_error(data, "Output dup outfile", 0);
	if (n)
	{
		if (dup2(data->end2[0], 0) < 0)
			on_error(data, "Output dup end2[0]", 0);
		if (close(data->end2[1]) < 0)
			on_error(data, "Output close end2[1]", 0);
	}
	else
	{
		if (dup2(data->end[0], 0) < 0)
			on_error(data, "Output dup end[0]", 0);
		if (close(data->end[1]) < 0)
			on_error(data, "Output close end[1]", 0);
	}
	if (close(data->outfile) < 0)
		on_error(data, "Output close outfile", 0);
	run_cmd(data, data->argv[data->argc - 2]);
}

#endif
