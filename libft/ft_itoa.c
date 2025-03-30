/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:16:14 by mzhivoto          #+#    #+#             */
/*   Updated: 2024/11/19 18:20:05 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digits(int n)
{
	size_t			count;
	unsigned int	num;

	count = 0;
	if (n <= 0)
		count = 1;
	if (n < 0)
		num = -n;
	else
		num = n;
	while (num > 0)
	{
		num /= 10;
		count++;
	}
	return (count);
}

static void	put_digit(char *string, unsigned int num, size_t string_len)
{
	while (num > 0)
	{
		string[--string_len] = (num % 10) + '0';
		num /= 10;
	}
}

char	*ft_itoa(int n)
{
	unsigned int	num;
	size_t			string_len;
	char			*string;

	string_len = count_digits(n);
	string = (char *)malloc((string_len + 1) * sizeof(char));
	if (!string)
		return (NULL);
	string[string_len] = '\0';
	if (n < 0)
	{
		string[0] = '-';
		num = -n;
	}
	else
		num = n;
	if (n == 0)
	{
		string[0] = '0';
		return (string);
	}
	put_digit(string, num, string_len);
	return (string);
}
