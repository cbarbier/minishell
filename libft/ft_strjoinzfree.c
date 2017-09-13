/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoinzfree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 12:31:51 by cbarbier          #+#    #+#             */
/*   Updated: 2017/09/13 15:13:13 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoinzfree(char const *s1, char const *s2, int n, int z)
{
	char	*res;
	int		len;

	if (!s2)
		return ((char *)s1);
	len = s1 ? ft_strlen(s1) : 0;
	if (!(res = ft_strnew(len + n)))
		return (0);
	if (s1)
		ft_strcpy(res, s1);
	ft_strncat(res, s2, n);
	if (z == 1 || z == 3)
		ft_strdel((char **)&s1);
	if (z == 2 || z == 3)
		ft_strdel((char **)&s2);
	return (res);
}
