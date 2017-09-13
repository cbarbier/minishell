/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 16:18:00 by cbarbier          #+#    #+#             */
/*   Updated: 2017/09/13 17:26:33 by cbarbier         ###   ########.fr       */
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

static int	parse_cmd(t_mns *mns, char **cmd)
{
	char		*val;

	while (*cmd)
	{
		ft_printf(" parsin %s\n", *cmd);
		if ((val = ft_strchr(*cmd, '~')))
		{
			ft_printf(" tilde %s\n", *cmd);
			replace_home(mns, cmd, val);
		}
		if (**cmd == '$' && (val = get_val(mns->envcpy, (*cmd) + 1)))
		{
			ft_printf(" dollar %s\n", *cmd);
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
