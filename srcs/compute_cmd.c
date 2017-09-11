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

static int		to_cmd_list(t_mns *mns, char **arg_tab)
{
	t_list		*elm;
	t_cmd		cmd;
	char		**tab;
	
	tab  = arg_tab;
	while (*tab)
	{
		cmd.args = ft_strsplitif(*tab, is_spaces);
		cmd.path = 0;
		if (!(elm = ft_lstnew(&cmd, sizeof(t_cmd))))
			return (0);
		ft_lstpushback(&mns->cmds, elm);
		tab++;
	}
	ft_strtabdel(&arg_tab);
	return (1);
}

static int		put_cmd(t_list *e, void *d)
{
	t_cmd	*cmd;

	(void)d;
	cmd = (t_cmd*)e->content;
	ft_printf("->path : %s", cmd->path);
	ft_putstrtab(cmd->args);
	return (0);
}

int			compute_cmd(t_mns *mns, int *run)
{
	char	**tab;

	(void)run;
	tab = ft_strsplit(mns->line, ';');
	to_cmd_list(mns, tab);
	ft_lstany(mns->cmds, put_cmd, 0);
	return (0);
}
