/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:01:56 by molasz-a          #+#    #+#             */
/*   Updated: 2024/03/07 17:02:11 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *s, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		words++;
		while (s[i] == c)
			i++;
	}
	return (words);
}

static int	count_chars(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	on_error(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (1);
}

static int	fill_strs(char **strs, char *s, char c, int words)
{
	int	word_len;
	int	word;
	int	i;
	int	j;

	i = 0;
	word = 0;
	while (word < words)
	{
		j = 0;
		while (s[i] == c)
			i++;
		word_len = count_chars(s + i, c);
		strs[word] = malloc((word_len + 2) * sizeof (char));
		if (!strs[word])
			return (on_error(strs));
		strs[word][word_len + 1] = '\0';
		while (s[i] && j < word_len)
			strs[word][j++] = s[i++];
		strs[word][j] = '/';
		word++;
	}
	return (0);
}

char	**ft_split_path(char *s, char c)
{
	char	**strs;
	int		words;

	words = count_words(s, c);
	strs = malloc((words + 1) * sizeof (char *));
	if (!strs)
		return (NULL);
	strs[words] = NULL;
	if (fill_strs(strs, s, c, words))
		return (NULL);
	return (strs);
}
