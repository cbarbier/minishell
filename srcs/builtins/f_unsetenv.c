/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_unsetenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:43:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/09/14 11:50:25 by cbarbier         ###   ########.fr       */
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
		if (!ft_strncmp(*tab, key, n))
			return (i);
		tab++;
		i++;
	}
	return (-1);
}

static char		**ft_strtabpop(char **tab, int ipop)
{
	int			n;
	int			inew;
	char		**new;
	char		**tmp;

	n = ft_strtablen(tab);
	tmp = tab;
	if (!(new = (char **)ft_memalloc(n * sizeof(char *))))
		return (0);
	inew = 0;
	while (*tab)
	{
		if (inew != ipop)
			new[inew++] = *tab++;
		else
			ft_strdel(tab++);
	}
	free(tmp);
	return (new);
}

int				f_unsetenv(t_mns *mns, char **cmd)
{
	int		i;

	if (ft_strtablen(cmd) != 2)
	{
		ft_fprintf(2, "mnsh: Usage: unsetenv [VAR_NAME]\n");
		return (0);
	}
	if ((i = get_env_index(mns->envcpy, cmd[1])) < 0)
		return (0);
	mns->envcpy = ft_strtabpop(mns->envcpy, i);
	return (1);
}
