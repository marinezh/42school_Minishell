/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:06:46 by mzhivoto          #+#    #+#             */
/*   Updated: 2024/11/19 18:22:44 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	safe_malloc(char **split_array, int position, size_t buffer)
{
	int	i;

	i = 0;
	split_array[position] = malloc(buffer);
	if (NULL == split_array[position])
	{
		while (i < position)
		{
			free(split_array[i++]);
		}
		free(split_array);
		return (1);
	}
	return (0);
}

static int	fill(char **split_array, char const *str, char delimeter)
{
	size_t	len;
	int		i;

	i = 0;
	while (*str)
	{
		len = 0;
		while (*str == delimeter && *str)
			++str;
		while (*str != delimeter && *str)
		{
			++len;
			++str;
		}
		if (len)
		{
			if (safe_malloc(split_array, i, len + 1))
				return (1);
			ft_strlcpy(split_array[i], str - len, len + 1);
			++i;
		}
	}
	return (0);
}

static size_t	count_words(const char *str, char delimiter)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str == delimiter)
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		str++;
	}
	return (count);
}

char	**ft_split(const char *str, char delimiter)
{
	size_t	words;
	char	**split_array;

	if (!str)
		return (NULL);
	words = 0;
	words = count_words(str, delimiter);
	split_array = malloc((words + 1) * sizeof(char *));
	if (!split_array)
		return (NULL);
	split_array [words] = NULL;
	if (fill(split_array, str, delimiter))
		return (NULL);
	return (split_array);
}
