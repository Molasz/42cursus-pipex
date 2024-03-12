/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 00:10:58 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/12 01:29:19 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#ifdef BONUS

void	here_doc(t_data *data)
{
	char *line;

	while (1)
	{
		line = get_next_line(0);
		if (!ft_strncmp(line, data->argv[0], ft_strlen(data->argv[0])))
			break ;
		write(data->end[1], line, ft_strlen(line));
		free(line);
	}
	pipe(data->end2);
	if (dup2(data->end2[0], 0) < 0)
		on_error(data, "Input dup infile", 0);
	if (dup2(data->end[1], 1) < 0)
		on_error(data, "Input dup end[1]", 0);
	if (close(data->end[0]) < 0)
		on_error(data, "Input close end[0]", 0);
	if (close(data->end2[1]) < 0)
		on_error(data, "Input close infile", 0);
	fprintf(stderr, "RUN: %s\n", data->argv[1]);
	run_cmd(data, data->argv[1]);
}

#endif
