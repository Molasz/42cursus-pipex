/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:32:06 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/07 23:42:01 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
#include <sys/wait.h>

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

int	on_error(char *s, int n);
int	child(t_data *data);
int	parent(t_data *data);

#endif
