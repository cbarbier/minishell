/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 12:31:51 by cbarbier          #+#    #+#             */
/*   Updated: 2017/09/26 19:40:14 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstcpy(t_list *lst, size_t content_size)
{
	t_list			*new;
	t_list			*tmp;

	new = 0;
	while (lst)
	{
		if (!(tmp = ft_lstnew(lst->content, content_size)))
			return (0);
		ft_lstpushback(&new, tmp);
		lst = lst->next;
	}
	return (new);
}
