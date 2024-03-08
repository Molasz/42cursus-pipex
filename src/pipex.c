/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:29:28 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/09 00:16:23 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	**get_path(char **envp)
{
	char	**path;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	path = ft_split_path(&envp[i][5], ':');
	return (path);
}

static void	open_files(t_data *data)
{
	int		fd1;
	int		fd2;

	fd1 = open(data->argv[0], O_RDONLY);
	if (data->append)
		fd2 = open(data->argv[data->argc - 1], O_CREAT | O_APPEND, 0644);
	else
		fd2 = open(data->argv[data->argc - 1], O_CREAT | O_RDWR | O_TRUNC,
				0644);
	if (fd1 < 0)
		on_error(data, "Open infile", 0);
	if (fd2 < 0)
		on_error(data, "Open outfile", 0);
	data->infile = fd1;
	data->outfile = fd2;
}

static void	pipe_call(t_data *data, int cmd, int *input_pid)
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

static int	pipex(t_data *data)
{
	int		end[2];
	int		status;
	pid_t	input_pid;
	pid_t	pipe_pid;
	pid_t	output_pid;

	data->end = end;
	pipe(end);
	input_pid = fork_call(data, input);
	pipe_pid = 0;
	while (pipe_pid < data->argc - 4)
		pipe_call(data, pipe_pid++, &input_pid);
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

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc < 5)
		on_error(&data, "Invalid arguments\n", 1);
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		if (argc == 5)
			on_error(&data, "Invalid arguments\n", 1);
		data.argc = argc - 2;
		data.argv = argv + 2;
		data.append = 1;
	}
	else
	{
		data.argc = argc - 1;
		data.argv = argv + 1;
		data.append = 0;
	}
	data.envp = envp;
	data.path = get_path(envp);
	if (!data.path)
		on_error(&data, "Path", 0);
	open_files(&data);
	return (pipex(&data));
}
