/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 16:18:00 by cbarbier          #+#    #+#             */
/*   Updated: 2017/09/14 11:51:33 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_home(t_mns *mns, char **tok, char *tild)
{
	char	*hom;
	char	*res;

	if (!(hom = get_val(mns->envcpy, "HOME")))
		return (0);
	res = ft_strjoin(hom, tild + 1);
	res = ft_strjoinfree(ft_strsub(*tok, 0, tild - *tok), res);
	ft_strdel(tok);
	*tok = res;
	return (1);
}

static int	set_status(t_mns *mns, char **cmd)
{
	char		*new;

	if (!(new = ft_itoa(mns->status)))
		return (0);
	ft_strdel(cmd);
	*cmd = new;
	return (1);
}

static int	parse_cmd(t_mns *mns, char **cmd)
{
	char		*val;

	while (*cmd)
	{
		if ((val = ft_strchr(*cmd, '~')))
		{
			replace_home(mns, cmd, val);
		}
		if (!ft_strcmp("$?", *cmd))
			set_status(mns, cmd);
		else if (**cmd == '$' && (val = get_val(mns->envcpy, (*cmd) + 1)))
		{
			ft_strdel(cmd);
			*cmd = ft_strdup(val);
		}
		cmd++;
	}
	return (1);
}

int			parse_token(t_mns *mns, char ***cmds)
{
	while (*cmds)
	{
		parse_cmd(mns, *cmds);
		cmds++;
	}
	return (1);
}
