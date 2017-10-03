/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fr33.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 15:03:55 by cbarbier          #+#    #+#             */
/*   Updated: 2017/10/03 18:34:08 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_mns_cmds(t_mns *mns)
{
	char	***start;
	char	***tmp;

	start = mns->cmds;
	while (*start)
	{
		tmp = start;
		start++;
		ft_strtabdel(tmp);
	}
	free(mns->cmds);
	mns->cmds = 0;
	mns->tcmds = 0;
}

void		free_mns(t_mns *mns)
{
	ft_strtabdel(&mns->envcpy);
	ft_strtabdel(&mns->keys);
	ft_strtabdel(&mns->paths);
	free_mns_cmds(mns);
	ft_strdel(&mns->err);
}
