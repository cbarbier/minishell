/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitif.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 12:31:51 by cbarbier          #+#    #+#             */
/*   Updated: 2017/05/09 09:24:42 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int				nb_words(char **aptr, int (*f)(char))
{
	unsigned int	nbwords;
	char			*ptr;

	ptr = *aptr;
	nbwords = 0;
	while (*ptr)
	{
		if (!f(*ptr))
		{
			if (!nbwords)
				*aptr = ptr;
			while (*ptr && !f(*ptr))
				ptr++;
			nbwords++;
		}
		else
			ptr++;
	}
	return (nbwords);
}

static	unsigned int	add_word(char *ptr, char **res, int (*f)(char))
{
	unsigned int	index;

	index = 0;
	while (!f(ptr[index]) && ptr[index])
		index++;
	*res = ft_strsub(ptr, 0, index);
	while (ptr[index] && f(ptr[index]))
		index++;
	return (index);
}

char					**ft_strsplitif(char const *s, int (*f)(char))
{
	char			**res;
	char			*ptr;
	unsigned int	i_res;
	unsigned int	nb;

	if (!s)
		return (NULL);
	ptr = (char *)s;
	nb = nb_words(&ptr, f);
	res = (char **)malloc((nb + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i_res = 0;
	while (i_res < nb)
	{
		ptr += add_word(ptr, &res[i_res], f);
		i_res++;
	}
	res[nb] = 0;
	return (res);
}
