/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:55:40 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/02/28 16:02:52 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_put_hex(unsigned long num)
{
	int			count;
	const char	*hex_digits;

	count = 0;
	hex_digits = "0123456789abcdef";
	if (num >= 16)
		count += ft_put_hex(num / 16);
	count += ft_putchar(hex_digits[num % 16]);
	return (count);
}

int	ft_putptr(void *ptr)
{
	int	count;

	count = 0;
	if (!ptr)
		return (ft_putstr("(nil)"));
	count += ft_putstr("0x");
	count += ft_put_hex((unsigned long)ptr);
	if (count < 0)
		return (-1);
	return (count);
}
