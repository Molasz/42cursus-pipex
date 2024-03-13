/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:29:28 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/13 14:51:57 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	open_files(t_data *data)
{
	int		fd1;
	int		fd2;

	fd1 = open(data->argv[0], O_RDONLY);
	if (fd1 < 0)
		on_error(data, "Open infile", 0);
	fd2 = open(data->argv[data->argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd2 < 0)
		on_error(data, "Open outfile", 0);
	data->infile = fd1;
	data->outfile = fd2;
}

static void	input_child(t_data *data)
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

static void	output_child(t_data *data)
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

static int	pipex(t_data *data)
{
	int		status[2];
	pid_t	pids[2];

	pipe(data->end);
	pids[0] = fork_call(data, input_child);
	pids[1] = fork_call(data, output_child);
	if (close(data->end[0]) < 0)
		on_error(data, "Close end[0]", 0);
	if (close(data->end[1]) < 0)
		on_error(data, "Close end[1]", 0);
	waitpid(pids[0], &status[0], 0);
	waitpid(pids[1], &status[1], 0);
	free_all(data);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data.path = NULL;
	if (argc != 5)
		on_error(&data, "Invalid arguments\n", 1);
	data.here_doc = 0;
	data.argc = argc - 1;
	data.argv = argv + 1;
	data.envp = envp;
	data.path = get_path(envp);
	if (!data.path)
		on_error(&data, "Path", 0);
	open_files(&data);
	return (pipex(&data));
}
