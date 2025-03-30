/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:14:21 by mzhivoto          #+#    #+#             */
/*   Updated: 2024/11/19 18:23:10 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		len;
	char	*dest;

	len = ft_strlen(src);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	ft_memcpy(dest, src, len);
	dest[len] = '\0';
	return (dest);
}
// The  strdup() function returns a pointer to a new string which is a du‐
// plicate of the string s.  Memory for the new string  is  obtained  with
// malloc(3), and can be freed with free(3).
// The strndup() function is similar, but copies at most n bytes.  If s is
// longer than n, only n bytes are copied, and  a  terminating  null  byte
// ('\0') is added.