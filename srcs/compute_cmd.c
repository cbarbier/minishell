/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:43:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/08/24 14:48:44 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		is_spaces(char c)
{
	if (ft_strchr(" \t", c))
		return (1);
	return (0);
}

static int		to_cmd_lists(t_mns *mns, char **tab)
{
	t_cmd	cmd;	

	while (*tab)
	{
		cmd.args = ft_strsplitif(*tab, is_spaces);
		cmd.path = 0;
		if (!(elm = ft_lstnew(&cmd, sizeof(t_cmd))))
			return (0);
		ft_lstpushback(&mns->cmds, elm);
		tab++;
	}
	ft_strtabdel(&tab);
	return (1);
}

int			compute_cmd(t_mns *mns, int *run)
{
	char	**tab;

	tab = ft_strplit(mns->line, ';');
	to_cmds_list(mns, tab);
	
	return (0);
}
