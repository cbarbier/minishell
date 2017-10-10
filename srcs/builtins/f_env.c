/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:43:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/10/10 10:55:54 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		f_env(t_mns *mns, char **cmd, char **env)
{
	char	**call_cmd;

	if (ft_strtablen(cmd) == 1)
	{
		ft_putstrtab(env);
		return (1);
	}
	else if (ft_strtablen(cmd) >= 3 && !ft_strcmp(cmd[1], "-i"))
	{
		call_cmd = cmd + 2;
		if (try_cmd(mns, cmd[2], call_cmd))
			exec_cmd(mns, cmd[2], call_cmd, 0);
		else
			ft_fprintf(2, "env: %s: No such file or directory\n", cmd[2]);
	}
	else
	{
		ft_fprintf(2, "env: Usage: env [-i utility]\n");
		return (0);
	}
	return (1);
}
