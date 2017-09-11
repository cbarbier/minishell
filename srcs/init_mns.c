/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:43:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/08/24 14:48:44 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_env(t_mns *mns, char **envp)
{
	while (*envp)
	{
		if (!ft_strncmp("PATH", *envp, 4))
			mns->paths = ft_strsplit((*envp) + 5, ':');
		mns->envcpy = ft_str_to_tab(mns->envcpy, *envp);
		envp++;
	}
	return (0);
}

static void	init_builtins(t_mns *mns)
{
	ft_strcpy(mns->bltins[0].name, "cd");
	mns->bltins[0].f = f_cd;
	ft_strcpy(mns->bltins[1].name, "env");
	mns->bltins[1].f = f_env;
	ft_strcpy(mns->bltins[2].name, "echo");
	mns->bltins[2].f = f_echo;
	ft_strcpy(mns->bltins[3].name, "setenv");
	mns->bltins[3].f = f_setenv;
	ft_strcpy(mns->bltins[4].name, "unsetenv");
	mns->bltins[4].f = f_unsetenv;
	ft_strcpy(mns->bltins[5].name, "exit");
	mns->bltins[5].f = f_exit;
}

int		init_mns(t_mns *mns, char **envp)
{
	ft_bzero(mns, sizeof(t_mns));
	init_builtins(mns);
	init_env(mns, envp);
	return (0);
}