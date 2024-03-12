/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:32:06 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/12 00:18:18 by molasz-a         ###   ########.fr       */
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

# ifndef BONUS

typedef struct s_data
{
	int		argc;
	char	**argv;
	char	**envp;
	char	**path;
	int		here_doc;
	int		*end;
	int		infile;
	int		outfile;
}			t_data;

# else

typedef struct s_data
{
	int		argc;
	char	**argv;
	char	**envp;
	char	**path;
	int		here_doc;
	int		end[2];
	int		end2[2];
	int		infile;
	int		outfile;
}			t_data;

# endif

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

void	here_doc(t_data *data);

# endif

#endif
