/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:14:21 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/04/29 22:23:31 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strndup(const char *s, size_t n)
{
	char	*dest;
	size_t		len;

	len = 0;
	while(s[len] && len < n)
		len++;
	dest = malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	ft_memcpy(dest, s, len);
	dest[len] = '\0';
	return (dest);
}

// The strndup() function is similar to strdup(), but copies at most n bytes.  If s is
// longer than n, only n bytes are copied, and  a  terminating  null  byte
// ('\0') is added.