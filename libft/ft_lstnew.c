/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:04:08 by ikozhina          #+#    #+#             */
/*   Updated: 2024/11/22 12:11:19 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*pnt;

	pnt = malloc(sizeof(t_list));
	if (!pnt)
		return (NULL);
	pnt->content = content;
	pnt->next = NULL;
	return (pnt);
}
