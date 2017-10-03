/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 16:18:00 by cbarbier          #+#    #+#             */
/*   Updated: 2017/10/03 18:01:40 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*replace_var(t_mns *mns, char **tok, char *dol)
{
	char	**keys;
	char	*res;
	int		len;
	int		tmp;

	if (!(keys = mns->keys))
		return (0);
	while (*keys)
	{
		len = ft_strlen(*keys);
		if (!ft_strncmp(dol + 1, *keys, len))
		{
			res = ft_strsub(*tok, 0, dol - *tok);
			res = ft_strnjoinzfree(res, get_val(mns->envcpy, *keys), -1, 1);
			tmp = ft_strlen(res);
			res = ft_strnjoinzfree(res, dol + len + 1, -1, 1);
			ft_strdel(tok);
			*tok = res;
			return (*tok + tmp);
		}
		keys++;
	}
	return (dol + 1);
}

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
	char		*tmp;

	while (*cmd)
	{
		tmp = *cmd;
		while ((tmp = ft_strchr(tmp, '$')))
			tmp = replace_var(mns, cmd, tmp);
		if ((val = ft_strchr(*cmd, '~')))
			replace_home(mns, cmd, val);
		if (!ft_strcmp("$?", *cmd))
			set_status(mns, cmd);
		cmd++;
	}
	return (1);
}

int			parse_token(t_mns *mns, char ***cmds)
{
	maj_keys(mns);
	while (*cmds)
	{
		parse_cmd(mns, *cmds);
		cmds++;
	}
	return (1);
}
