/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstreverse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 09:37:00 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/07 09:37:31 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void		ft_lstreverse(t_list **alst)
{
	t_list	*lst;
	t_list	*tmp;
	t_list	*tmp2;

	if (!alst)
		return ;
	lst = *alst;
	tmp = 0;
	while (lst)
	{
		tmp2 = lst->next;
		lst->next = tmp;
		tmp = lst;
		lst = tmp2;
	}
	if (tmp)
		*alst = tmp;
}
