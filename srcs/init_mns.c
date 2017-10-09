/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:43:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/10/09 15:23:44 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	up_sh_lvl(char **envcpy)
{
	char	*val;
	int		lvl;

	val = get_val(envcpy, "SHLVL");
	if (!ft_myatoi(val, &lvl))
		return (0);
	set_val(envcpy, "SHLVL", ft_itoa(lvl + 1));
	return (1);
}

static int	init_env(t_mns *mns)
{
	char		*pa;
	char		*pb;
	char		*h;

	if ((h = get_val(mns->envcpy, "HOME")))
		chdir(h);
	pa = getcwd(0, 0);
	if (!get_val(mns->envcpy, "PWD") && pa)
		mns->envcpy = ft_str_to_tab(mns->envcpy, ft_strjoin("PWD=", pa));
	else if (pa)
		set_val(mns->envcpy, "PWD", ft_strdup(pa));
	if (!get_val(mns->envcpy, "_") && pa)
	{
		pb = ft_strnjoinzfree("_=", pa, ft_strlen(pa), 0);
		pb = ft_strnjoinzfree(pb, "/minishell", 10, 1);
		mns->envcpy = ft_str_to_tab(mns->envcpy, pb);
	}
	if (!get_val(mns->envcpy, "SHLVL") && pa)
		mns->envcpy = ft_str_to_tab(mns->envcpy, ft_strdup("SHLVL=0"));
	ft_strdel(&pa);
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

int			init_mns(t_mns *mns, char **envp)
{
	ft_bzero(mns, sizeof(t_mns));
	init_builtins(mns);
	while (*envp)
	{
		if (!ft_strncmp("PATH", *envp, 4))
			mns->paths = ft_strsplit((*envp) + 5, ':');
		mns->envcpy = ft_str_to_tab(mns->envcpy, ft_strdup(*envp));
		envp++;
	}
	init_env(mns);
	up_sh_lvl(mns->envcpy);
	mns->run = 1;
	return (1);
}
