/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 09:53:46 by cbarbier          #+#    #+#             */
/*   Updated: 2017/05/09 10:48:51 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static char	**create_tab(char *str)
{
	char		**new;

	if (!(new = (char **)ft_memalloc(2 * sizeof(char *))))
		return (0);
	new[0] = str;
	return (new);
}

char		**ft_str_to_tab(char **tab, char *str)
{
	char	**new;
	int		len;

	if (!tab)
		return (create_tab(str));
	len = 0;
	while (tab[len])
		len++;
	if (!(new = (char **)ft_memalloc((len + 2) * sizeof(char *))))
		return (0);
	ft_memcpy((void *)new, (void *)tab, len * sizeof(char *));
	new[len] = str;
	free(tab);
	return (new);
}
