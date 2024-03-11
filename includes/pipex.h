/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:32:06 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/11 15:35:18 by molasz-a         ###   ########.fr       */
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
	int		*end2;
	int		infile;
	int		outfile;
}			t_data;

void	input_child(t_data *data);
void	output_child(t_data *data);

void	free_all(t_data *data);
int		on_error(t_data *data, char *s, int n);
void	run_cmd(t_data *data, char *cmd);
pid_t	fork_call(t_data *data, void (*f)(t_data *));

# ifdef BONUS

int		pipex_bonus(t_data *data);

void	pipe_pipe2_child(t_data *data, int cmd);
void	pipe2_pipe_child(t_data *data, int cmd);
void	output_child_bonus(t_data *data, int n);

# endif

#endif
