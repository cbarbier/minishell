/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfilter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:04:31 by cbarbier          #+#    #+#             */
/*   Updated: 2017/07/24 18:25:05 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include "includes/ft_lst.h"

int		ft_lstfilter(t_list **al, void (*del)(void*, size_t),
int (*f)(void *, void *), void *data)
{
	t_list	*l;
	t_list	*tmp;
	t_list	*next;

	if (!al || !(l = *al))
		return (0);
	tmp = 0;
	while (l)
	{
		if (f(l->content, data))
		{
			next = l->next;
			if (!tmp)
				*al = l->next;
			else
				tmp->next = l->next;
			ft_lstdelone(&l, del);
		}
		else
			tmp = l;
		l = (tmp ? tmp->next : next);
	}
	return (1);
}
