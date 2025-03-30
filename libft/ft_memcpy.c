/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:57:03 by mzhivoto          #+#    #+#             */
/*   Updated: 2024/11/19 18:21:04 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
// The memcpy() function copies n bytes from memory area src to memory 
// area dst. If dst and src overlap, behavior is undefined.
//  Applications in which dst and src might overlap should use memove(3) 
//instead. The memcpy() function returns the original value of dst.
//  This functions works like the strcpy function, except that memcpy 
//  accepts  void * as parameters, so we can give it any type of pointer
//   we want to copy.
