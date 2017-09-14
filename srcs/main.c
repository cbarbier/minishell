/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:43:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/09/14 16:50:44 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sig_handler(int sig)
{
	(void)sig;
}

static void	put_prompt(t_mns *mns)
{
	char	*p;

	if (!(p = get_val(mns->envcpy, "PWD")))
		ft_printf("\e[36;1m mnshll-$>{no}");
	else
		ft_printf("[{grn}%s{no}]\e[36;1m mnshll-$>{no}", p);
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
	signal(SIGINT, sig_handler);
	init_mns(&mns, envp);
	mns_core(&mns);
	return (0);
}
