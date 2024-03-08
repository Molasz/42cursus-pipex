/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:14:24 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/08 19:19:57 by molasz-a         ###   ########.fr       */
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
	exit(EXIT_FAILURE);
}
