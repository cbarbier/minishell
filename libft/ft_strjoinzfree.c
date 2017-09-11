/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 12:31:51 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/14 14:11:42 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinzfree(char const *s1, char const *s2, int n)
{
	char	*res;
	int	len;

	if (!s2)
		return ((char *)s1);
	len = s1 ? ft_strlen(s1) : 0;
	if (!(res = ft_strnew(len + ft_strlen(s2))))
		return (NULL);
	if (s1)
		ft_strcpy(res, s1);
	ft_strcat(res, s2);
	if (n == 1 || n == 3)
		ft_strdel((char **)&s1);
	if (n == 2 || n == 3)
		ft_strdel((char **)&s2);
	return (res);
}
