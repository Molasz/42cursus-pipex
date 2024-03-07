/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:54:32 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/07 20:28:38 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	run_cmd(t_data *data)
{
	char	**args;
	int		priv;
	int		i;

	args = ft_split(data->argv[1], ' ');
	i = 0;
	while (data->path[i])
	{
		priv = access(data->path[i], F_OK);
		if (!priv)
			break ;
		i++;
	}
	printf("CHILD\n");
	if (data->path[i])
		execve(data->path[i], args, data->envp);
	else
		printf("NOT FOUND\n");
}

int	child(t_data *data)
{
	printf("A\n");
	if (dup2(data->infile, 0) < 0)
		on_error("Dup infile");
	printf("B\n");
	if (dup2(data->end[1], 1) < 0)
		on_error("Dup end[1]");
	printf("C\n");
	if (close(data->end[0]) < 0)
		on_error("Close end[0]");
	printf("D\n");
	if (close(data->outfile) < 0)
		on_error("Close outfile");
	printf("E\n");
	run_cmd(data);
	return (EXIT_SUCCESS);
}

