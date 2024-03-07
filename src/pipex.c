/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:29:28 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/07 13:52:36 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	on_error(char *s)
{
	if (s)
	{
		write(2, "Error: ", 7);
		write(2, s, ft_strlen(s));
		write(2, "\n", 1);
	}
	else
		perror("Error");
	exit(EXIT_FAILURE);
}

static char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	return (envp[i]);
}

static int	pipex(char **params, char *path, int append)
{
	int		end[2];
	pid_t	pid;

	pipe(end);
	pid = fork();
	if (pid < 0)
		return (on_error(NULL));
	if (!pid)
		child(params, path, append);
	else
		parent(params, path, append);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
		on_error("Incorrect arguments");
	else if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		if (argc == 5)
			on_error("Incorrect arguments");
		else
			pipex(argv + 2, get_path(envp), 1);
	}
	else
		pipex(argv + 1, get_path(envp), 0);
	return (EXIT_SUCCESS);
}
