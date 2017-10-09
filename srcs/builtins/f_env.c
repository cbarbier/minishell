/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:43:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/10/09 13:19:48 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		f_env(t_mns *mns, char **cmd)
{
	if (ft_strtablen(cmd) > 1)
	{
		ft_fprintf(2, "env: Usage: env [no arguments]\n");
		return (0);
	}
	ft_putstrtab(mns->envcpy);
	return (1);
}
