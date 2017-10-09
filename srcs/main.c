/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:43:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/10/09 13:36:35 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_prompt(t_mns *mns)
{
	char	*p;
	char	*h;
	char	*pwd;

	if (!(p = get_val(mns->envcpy, "PWD")))
	{
		if (!(pwd = getcwd(0, 0)) && ft_printf("\e[36;1m mnshll-$>{no}"))
			return ;
		mns->envcpy = ft_str_to_tab(mns->envcpy, ft_strjoin("PWD=", pwd));
		ft_printf("[{grn}%s{no}]\e[36;1m mnshll-$>{no}", pwd);
		ft_strdel(&pwd);
		return ;
	}
	else if ((h = get_val(mns->envcpy, "HOME"))
			&& !ft_strncmp(p, h, ft_strlen(h)))
		ft_printf("[{grn}~%s{no}]", p + ft_strlen(h));
	else
		ft_printf("[{grn}%s{no}]", (p ? p : ""));
	ft_printf("\e[36;1m mnshll-$>{no}");
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
		put_prompt(mns);
		line_reader(mns, 0);
		parse_token(mns, mns->cmds);
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
	signal(SIGINT, SIG_IGN);
	init_mns(&mns, envp);
	mns_core(&mns);
	return (0);
}
