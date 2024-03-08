/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:32:06 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/08 23:57:13 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>

typedef struct s_data
{
	int		argc;
	char	**argv;
	char	**envp;
	char	**path;
	int		append;
	int		*end;
	int		infile;
	int		outfile;
}			t_data;

void	input(t_data *data);
void	pipes(t_data *data, int cmd);
void	output(t_data *data);

int		on_error(t_data *data, char *s, int n);
void	free_all(t_data *data);
void	run_cmd(t_data *data, char *cmd);
pid_t	fork_call(t_data *data, void (*f)(t_data *));

#endif
