/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:43:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/10/10 09:09:31 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		f_env(t_mns *mns, char **cmd)
{
	char	**call_cmd;

	if (ft_strtablen(cmd) == 1)
	{
		ft_putstrtab(mns->envcpy);
		return (1);
	}
	else if (ft_strtablen(cmd) >= 3 && !ft_strcmp(cmd[1], "-i"))
	{
		call_cmd = cmd + 2;
		treat_cmd(mns, &call_cmd);
	}
	else
	{
		ft_fprintf(2, "env: Usage: env [no arguments]\n");
		return (0);
	}
	return (1);
}
