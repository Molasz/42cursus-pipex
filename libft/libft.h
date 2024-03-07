/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:43:39 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/08 00:22:15 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# include <stdio.h> 
# include <stdlib.h>

int		ft_strlen(char *s);
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char *s, char c);
char	**ft_split_path(char *s, char c);

#endif
