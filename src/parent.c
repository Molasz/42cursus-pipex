/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:52:57 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/07 23:44:08 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	run_cmd(t_data *data)
{
	char	**args;
	int		priv;
	int		i;

	args = ft_split(data->argv[2], ' ');
	i = 0;
	while (data->path[i])
	{
		priv = access(data->path[i], F_OK);
		if (!priv)
			break ;
		i++;
	}
	if (data->path[i])
		execve(data->path[i], args, data->envp);
	else
		write(2, "NOT FOUND\n", 10);
}

int	parent(t_data *data)
{
	printf("PARENT\n");
	if (dup2(data->outfile, 1) < 0)
		on_error("Dup infile", 0);
	if (dup2(data->end[0], 0) < 0)
		on_error("Dup end[0]", 0);
	if (close(data->end[0]) < 0)
		on_error("Close end[0]", 0);
	if (close(data->outfile) < 0)
		on_error("Close outfile", 0);
	run_cmd(data);
	return (EXIT_SUCCESS);
}
