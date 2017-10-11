/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:43:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/10/11 13:28:40 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_prompt(t_mns *mns)
{
	char	*p;
	char	*h;

	p = getcwd(0, 0);
	if (p && (h = get_val(mns->envcpy, "HOME"))
			&& !ft_strncmp(p, h, ft_strlen(h)))
		ft_printf("[{grn}~%s{no}]", p + ft_strlen(h));
	else
		ft_printf("[{grn}%s{no}]", (p ? p : ""));
	ft_printf("\e[36;1m mnshll-$>{no}");
	ft_strdel(&p);
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
			if (!treat_cmd(mns, cmds++, mns->envcpy))
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
	if (argc != 1)
		return (ft_printf("Usage: ./minishell [NO ARGUMENT]\n") || 1);
	signal(SIGINT, SIG_IGN);
	init_mns(&mns, envp);
	mns_core(&mns);
	return (0);
}
