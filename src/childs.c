/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:16:05 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/08 19:24:52 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	run_cmd(t_data *data, char *cmd)
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
		execve(filepath, args, data->envp);
	else
		on_error(data, "Error: command not found\n", 1);
}

void	input(t_data *data)
{
	if (dup2(data->infile, 0) < 0)
		on_error(data, "Dup infile", 0);
	if (dup2(data->end[1], 1) < 0)
		on_error(data, "Dup end[1]", 0);
	if (close(data->end[0]) < 0)
		on_error(data, "Close end[0]", 0);
	if (close(data->infile) < 0)
		on_error(data, "Close infile", 0);
	run_cmd(data, data->argv[1]);
}

void	pipes(t_data *data, int cmd)
{
	if (dup2(data->end[0], 0) < 0)
		on_error(data, "Dup end[0]", 0);
	if (dup2(data->end[1], 1) < 0)
		on_error(data, "Dup end[1]", 0);
	if (close(data->end[0]) < 0)
		on_error(data, "Close end[0]", 0);
	if (close(data->end[1]) < 0)
		on_error(data, "Close end[1]", 0);
	run_cmd(data, data->argv[cmd + 1]);
}

void	output(t_data *data)
{
	if (dup2(data->outfile, 1) < 0)
		on_error(data, "Dup outfile", 0);
	if (dup2(data->end[0], 0) < 0)
		on_error(data, "Dup end[0]", 0);
	if (close(data->end[1]) < 0)
		on_error(data, "Close end[1]", 0);
	if (close(data->outfile) < 0)
		on_error(data, "Close outfile", 0);
	run_cmd(data, data->argv[data->argc - 2]);
}