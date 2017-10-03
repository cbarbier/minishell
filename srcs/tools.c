/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 11:18:56 by cbarbier          #+#    #+#             */
/*   Updated: 2017/10/03 16:38:43 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			maj_keys(t_mns *mns)
{
	char	**env;
	int		i;

	if (!(env = mns->envcpy))
		return (0);
	ft_strtabdel(&mns->keys);
	while (*env)
	{
		i = 0;
		while ((*env)[i] && (*env)[i] != '=')
			i++;
		mns->keys = ft_str_to_tab(mns->keys, ft_strsub(*env, 0, i));
		env++;
	}
	return (1);
}

char		*get_val(char **tab, const char *key)
{
	int		n;

	if (!tab)
		return (0);
	n = ft_strlen(key);
	while (*tab)
	{
		if (!ft_strncmp(*tab, key, n) && (*tab)[n] == '=')
			return ((*tab) + n + 1);
		tab++;
	}
	return (0);
}

int			set_val(char **tab, const char *key, char *val)
{
	int			n;
	char		*line;

	n = ft_strlen(key);
	while (*tab)
	{
		if (!ft_strncmp(*tab, key, n) && (*tab)[n] == '=')
		{
			ft_strdel(tab);
			line = ft_strjoin(key, "=");
			*tab = ft_strjoinfree(line, val);
			return (1);
		}
		tab++;
	}
	ft_strdel(&val);
	return (0);
}

int			found_cmd(char *path, char *cmd)
{
	DIR				*pdir;
	struct dirent	*dp;

	if (!(pdir = opendir(path)))
		return (0);
	while ((dp = readdir(pdir)))
	{
		if (!ft_strcmp(dp->d_name, cmd))
		{
			closedir(pdir);
			return (1);
		}
	}
	closedir(pdir);
	return (0);
}
