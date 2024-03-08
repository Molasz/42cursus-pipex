/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:29:28 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/08 17:37:17 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	on_error(char *s, int n)
{
	if (!n)
		perror(s);
	else
		write(2, s, ft_strlen(s));
	exit(EXIT_FAILURE);
}

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
		on_error("Open infile", 0);
	if (fd2 < 0)
		on_error("Open outfile", 0);
	data->infile = fd1;
	data->outfile = fd2;
}

static void	pipex(t_data *data)
{
	int		end[2];
	int		input_status;
	int		output_status;
	pid_t	input_pid;
	pid_t	output_pid;

	data->end = end;
	pipe(end);
	input_pid = fork();
	if (input_pid < 0)
		on_error("Fork pipe", 0);
	if (!input_pid)
		input(data);
	output_pid = fork();
	if (output_pid < 0)
		on_error("Fork pipe", 0);
	if (!output_pid)
		output(data);
	if (close(data->end[0]) < 0)
		on_error("Close end[0]", 0);
	if (close(data->end[1]) < 0)
		on_error("Close end[1]", 0);
	waitpid(input_pid, &input_status, 0);
	waitpid(output_pid, &output_status, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc < 5)
		on_error("Invalid arguments\n", 1);
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		if (argc == 5)
			on_error("Invalid arguments\n", 1);
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
		on_error("Path", 0);
	open_files(&data);
	pipex(&data);
	return (EXIT_SUCCESS);
}
