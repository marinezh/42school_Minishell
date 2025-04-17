/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:47:53 by ikozhina          #+#    #+#             */
/*   Updated: 2024/11/22 10:03:33 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*pnt;

	pnt = lst;
	if (!lst)
		return (NULL);
	while (pnt->next != NULL)
		pnt = pnt->next;
	return (pnt);
}
