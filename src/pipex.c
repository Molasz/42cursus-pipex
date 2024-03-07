/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:29:28 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/07 20:25:24 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	on_error(char *s)
{
	perror(s);
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
		fd2 = open(data->argv[data->argc - 1], O_CREAT | O_APPEND, 644);
	else
		fd2 = open(data->argv[data->argc - 1], O_CREAT | O_RDWR | O_TRUNC,
				644);
	if (fd1 < 0)
		on_error("Open in file");
	if (fd2 < 0)
		on_error("Open out file");
	data->infile = fd1;
	data->outfile = fd2;
}

static void pipex(t_data *data)
{
	int		end[2];
	int		pipes;
	int		status;
	pid_t	pid;

	pipes = 0;
	pipe(end);
	while (pipes < data->argc - 3)
	{
		pid = fork();
		if (pid < 0)
			on_error("Fork pipe");
		if (!pid)
			child(data);
		pipes++;
		waitpid(pid, &status, 0);
	}
	pid = fork();
	if (pid < 0)
		on_error("Fork outfile");
	if (!pid)
		parent(data);
	else
	{
		waitpid(pid, &status, 0);
		printf("END\n");
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc < 5)
		on_error("Arguments");
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		if (argc == 5)
			on_error("Arguments");
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
		on_error("Path");
	open_files(&data);
	pipex(&data);
	return (EXIT_SUCCESS);
}
