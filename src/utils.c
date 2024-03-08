/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:14:24 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/08 23:56:53 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_all(t_data *data)
{
	int	i;

	if (data->path)
	{
		i = 0;
		while (data->path[i])
			free(data->path[i++]);
		free(data->path);
	}
}

int	on_error(t_data *data, char *s, int n)
{
	if (!n)
		perror(s);
	else
		write(2, s, ft_strlen(s));
	free_all(data);
	if (!n)
		exit(errno);
	else
		exit(EXIT_FAILURE);
}

void	run_cmd(t_data *data, char *cmd)
{
	char	**args;
	char	*filepath;
	int		priv;
	int		i;

	args = ft_split(cmd, ' ');
	i = 0;
	while (data->path[i])
	{
		filepath = ft_strjoin(data->path[i], args[0]);
		if (!filepath)
			on_error(data, "Strjoin", 0);
		priv = access(filepath, F_OK);
		if (!priv)
			break ;
		free(filepath);
		i++;
	}
	if (data->path[i])
	{
		if (execve(filepath, args, data->envp) < 0)
			on_error(data, "EXECVE", 0);
	}
	else
		on_error(data, "Error: command not found\n", 1);
}

pid_t	fork_call(t_data *data, void (*f)(t_data *))
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		on_error(data, "Fork pipe", 0);
	if (!pid)
		f(data);
	return (pid);
}

