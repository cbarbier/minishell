/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 11:18:56 by cbarbier          #+#    #+#             */
/*   Updated: 2017/09/13 18:34:09 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_val(char **tab, const char *key)
{
	int		n;

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
