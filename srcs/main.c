/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:43:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/09/12 22:12:58 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sig_handler(int sig)
{
	(void)sig;
}

char		*get_val(char **tab, const char *key)
{
	int		i;
	int		n;

	n = ft_strlen(key);
	while (*tab)
	{
		if (!ft_strncmp(*tab, key, n) && (*tab)[n] == '=')
			return ((*tab) + n + 1);
		tab++;
		i++;
	}
	return (0);
}

int		set_val(char **tab, const char *key, char *val)
{
	int		n;
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

static int	mns_core(t_mns *mns)
{
	char	***cmds;
	int		i;

	i = 0;
	while (mns->run)
	{
		if (!(mns->cmds = (char***)ft_memalloc(2 * sizeof(char**))))
			return (0);
		mns->tcmds = mns->cmds;
		ft_printf("{blu}$mnshll>{no}");
		line_reader(mns, 0);
		cmds = mns->cmds;
		while (*cmds)
		{
			if (!treat_cmd(mns, cmds++))
				ft_fprintf(2, "%s", mns->err);
			ft_strdel(&mns->err);
		}
		free_mns_cmds(mns);
	}
	return (1);
}

int			main(int argc, char **argv, char **envp)
{
	t_mns		mns;

	(void)argv;
	(void)argc;
	signal(SIGINT, sig_handler);
	init_mns(&mns, envp);
	mns_core(&mns);
	return (0);
}
