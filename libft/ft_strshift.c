/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strshift.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 15:06:45 by cbarbier          #+#    #+#             */
/*   Updated: 2017/04/28 15:09:19 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void			ft_strshift(char **data, char c)
{
	char *tmp;
	char *pos;

	tmp = *data;
	if (!(pos = ft_strchr(tmp, c)))
		*data = ft_strnew(0);
	else
		*data = ft_strdup(pos + 1);
	free(tmp);
}
