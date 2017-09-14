/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_setenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:43:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/09/14 16:49:12 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		get_env_index(char **tab, char *key)
{
	int		i;
	int		n;

	n = ft_strlen(key);
	i = 0;
	while (*tab)
	{
		if (!ft_strncmp(*tab, key, n) && (*tab)[n] == '=')
			return (i);
		tab++;
		i++;
	}
	return (-1);
}

static int		is_valid_name(char *nm)
{
	while (*nm)
	{
		if (!ft_strchr("abcdefghijklmnopqrstuvwxyz", *nm)
			&& !ft_strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ_", *nm))
			return (0);
		nm++;
	}
	return (1);
}

int				f_setenv(t_mns *mns, char **cmd)
{
	int		i;
	char	*line;

	if (ft_strtablen(cmd) != 3
	|| !is_valid_name(cmd[1]))
	{
		ft_fprintf(2, "mnsh: Usage: setenv [VAR_NAME] [value] (A-Za-z_)\n");
		return (0);
	}
	line = ft_strjoin(cmd[1], "=");
	line = ft_strnjoinzfree(line, cmd[2], ft_strlen(cmd[2]), 1);
	if ((i = get_env_index(mns->envcpy, cmd[1])) < 0)
	{
		mns->envcpy = ft_str_to_tab(mns->envcpy, line);
		return (1);
	}
	ft_strdel(mns->envcpy + i);
	mns->envcpy[i] = line;
	return (1);
}
