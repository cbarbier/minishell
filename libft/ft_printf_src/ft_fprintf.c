/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 10:38:54 by cbarbier          #+#    #+#             */
/*   Updated: 2017/03/04 14:56:35 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int			ft_fprintf(int fd, const char *format, ...)
{
	int			ret;
	t_pf		pf;
	va_list		ap;

	init_pf(&pf);
	pf.ap = &ap;
	va_start(*(pf.ap), format);
	split_args(&pf, format);
	va_end(*(pf.ap));
	if (pf.ret != -1)
		write(fd, pf.buf, pf.ret);
	ret = pf.ret;
	ft_strdel(&(pf.buf));
	return (ret);
}
