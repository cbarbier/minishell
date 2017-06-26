/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_myatoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 12:05:14 by cbarbier          #+#    #+#             */
/*   Updated: 2017/05/09 10:48:20 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int		skip_chars(char *str, unsigned int *ind, const char *to_skip)
{
	unsigned int		i;

	i = 0;
	while (str[i] && ft_strchr(to_skip, str[i]))
		i++;
	*ind = (*ind) + i;
	return (i);
}

int				ft_myatoi(char *str, int *a)
{
	unsigned int	res;
	unsigned int	i;
	int				sign;

	res = 0;
	i = 0;
	sign = 1;
	if (!str || !*str)
		return (0);
	skip_chars(str + i, &i, " \t");
	if (str[i] == '-' || str[i] == '+')
		sign = (str[i++] == '-' ? -1 : 1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = 10 * res + str[i] - '0';
		if ((sign > 0 && res > 2147483647) || (sign < 0 && res > 2147483648))
			return (0);
		i++;
	}
	skip_chars(str + i, &i, " \t");
	*a = sign * res;
	return (str[i] ? 0 : 1);
}
