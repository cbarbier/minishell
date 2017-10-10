/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:43:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/10/10 09:15:30 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		f_exit(t_mns *mns, char **cmd, char **env)
{
	int		n;

	(void)env;
	n = 0;
	if (ft_strtablen(cmd) > 2)
	{
		ft_fprintf(2, "exit: Usage exit [n] (with n in [0:255])\n");
		return (0);
	}
	if (cmd[1] && !ft_myatoi(cmd[1], &n))
	{
		ft_fprintf(2, "exit: Usage exit [n] (with n in [0:255])\n");
		return (0);
	}
	free_mns(mns);
	exit(n);
	return (0);
}
