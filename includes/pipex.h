/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:32:06 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/07 13:55:36 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h>
# include <errno.h>
# include <stdio.h>

int	child(char **params, char *path, int append);
int	parent(char **params, char *path, int append);

#endif
