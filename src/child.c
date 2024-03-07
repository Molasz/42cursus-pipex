/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:54:32 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/08 00:32:16 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	run_cmd(t_data *data)
{
	char	**args;
	char	*filepath;
	int		priv;
	int		i;

	args = ft_split(data->argv[1], ' ');
	i = 0;
	while (data->path[i])
	{
		filepath = ft_strjoin(data->path[i], args[0]);
		if (!filepath)
			on_error("Filepath join", 0);
		printf("%s\n", filepath);
		priv = access(filepath, F_OK);
		free(filepath);
		if (!priv)
			break ;
		i++;
	}
	printf("CHILD %s\n", data->path[i]);
	if (data->path[i])
		execve(data->path[i], args, data->envp);
	else
		printf("NOT FOUND\n");
}

int	child(t_data *data)
{
	if (dup2(data->infile, 0) < 0)
		on_error("Dup infile", 0);
	if (dup2(data->end[1], 1) < 0)
		on_error("Dup end[1]", 0);
	if (close(data->end[0]) < 0)
		on_error("Close end[0]", 0);
	if (close(data->outfile) < 0)
		on_error("Close outfile", 0);
	run_cmd(data);
	return (EXIT_SUCCESS);
}

