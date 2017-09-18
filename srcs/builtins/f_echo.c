/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:43:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/09/18 13:44:05 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		f_echo(t_mns *mns, char **cmd)
{
	char		**arg;
	int			dashn;

	(void)mns;
	(void)cmd;
	arg = cmd + 1;
	dashn = *arg && !ft_strcmp(*arg, "-n") && ++arg ? 1 : 0;
	while (*arg)
	{
		ft_printf("%s", *arg++);
		if (*(arg))
			write(1, " ", 1);
	}
	if (!dashn)
		write(1, "\n", 1);
	return (1);
}
