/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:14:21 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/04/29 11:58:59 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strndup(const char *s, size_t n)
{
	char	*dest;
	size_t		len;
	size_t		i;

	len = 0;
	i = 0;
	while(s[i] && i < n)
		len++;

	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	dest[len] = '\0';
	ft_memcpy(dest, s, n);
	return (dest);
}

// The strndup() function is similar to strdup(), but copies at most n bytes.  If s is
// longer than n, only n bytes are copied, and  a  terminating  null  byte
// ('\0') is added.