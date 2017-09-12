/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:43:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/09/12 18:26:59 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		f_echo(t_mns *mns, char **cmd)
{
	char		**arg;

	(void)mns;
	(void)cmd;
	arg = cmd + 1;
	while (*arg)
	{
		ft_printf("%s", *arg++);
		if (*(arg))
			write(1, " ", 1);
	}
	write(1, "\n", 1);
	return (0);
}
