/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:15:29 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/17 15:55:56 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	cmd_forks(t_data *data)
{
	int	i;

	i = 0;
	while (++i < data->argc - 2)
	{
		if (pipe(data->end) < 0)
			on_error(data, "Pipe", 0);
		if (i == 1 && data->infile < 0)
		{
			if (dup2(data->end[0], 0) < 0)
				on_error(data, "Parent dup end[0]", 0);
			if (close(data->end[1]) < 0)
				on_error(data, "Parent close end[1]", 0);
			continue ;
		}
		fork_bonus(data, i);
	}
}

static void	dup_infile(t_data *data)
{
	data->infile = 0;
	if (data->here_doc)
		here_doc(data);
	else
	{
		data->infile = open(data->argv[0], O_RDONLY);
		if (data->infile < 0)
			perror("Infile");
		else
		{
			if (dup2(data->infile, 0) < 0)
				on_error(data, "Input dup infile", 0);
			if (close(data->infile) < 0)
				on_error(data, "Input close infile", 0);
		}
	}
}

static void	write_output(t_data *data)
{
	if (!data->here_doc)
		data->outfile = open(data->argv[data->argc - 1],
				O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		data->outfile = open(data->argv[data->argc - 1],
				O_CREAT | O_RDWR | O_APPEND, 0644);
	if (data->outfile < 0)
		on_error(data, "Outfile", 0);
	if (dup2(data->outfile, 1) < 0)
		on_error(data, "Output dup outfile", 0);
	if (close(data->outfile) < 0)
		on_error(data, "Output close outfile", 0);
	run_cmd(data, data->argv[data->argc - 2]);
}

static int	pipex(t_data *data)
{
	int	status;
	int	i;

	dup_infile(data);
	cmd_forks(data);
	fork_call(data, write_output);
	i = 0;
	if (data->infile < 0)
		i = 1;
	status = 0;
	while (i++ < data->argc - 2)
		waitpid(-1, &status, 0);
	free_all(data);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data.path = NULL;
	if (argc < 5)
		on_error(&data, "Invalid arguments\n", 1);
	if (!ft_strncmp(argv[1], "here_doc\0", 9))
	{
		if (argc == 5)
			on_error(&data, "Invalid arguments\n", 1);
		data.here_doc = 1;
		data.argc = argc - 2;
		data.argv = argv + 2;
	}
	else
	{
		data.here_doc = 0;
		data.argc = argc - 1;
		data.argv = argv + 1;
	}
	data.envp = envp;
	data.path = get_path(envp);
	if (!data.path)
		on_error(&data, "Path", 0);
	return (pipex(&data));
}
