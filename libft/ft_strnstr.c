/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:52:48 by mzhivoto          #+#    #+#             */
/*   Updated: 2024/11/19 18:24:37 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *small, size_t l)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*small == '\0')
	{
		return ((char *)big);
	}
	while (i < l && big[i] != '\0')
	{
		j = 0;
		while ((i + j < l && big[i + j] && small[j] && big[i + j] == small[j]))
		{
			j++;
		}
		if (small[j] == '\0')
		{
			return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
