/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:43:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/09/14 11:47:17 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*make_fullpath(char *pa)
{
	char		*fp;
	char		*wd;

	if (!(wd = getcwd(0, 0)))
		return (0);
	wd = ft_strnjoinzfree(wd, "/", 1, 1);
	fp = ft_strjoin(wd, pa);
	ft_strdel(&wd);
	return (fp);
}

static int	is_valid_dir(t_mns *mns, char *pa)
{
	struct stat		st;
	char			*fp;
	int				ret;

	(void)mns;
	ret = 1;
	if (pa[0] != '/')
		fp = make_fullpath(pa);
	else
		fp = ft_strdup(pa);
	if ((stat(pa, &st) == -1) && !(ret = 0))
		ft_fprintf(2, "cd: no such file or directory: %s\n", pa);
	else if (!(S_ISDIR(st.st_mode)) && !(ret = 0))
		ft_fprintf(2, "cd: not a directory: %s\n", pa);
	else if (!(st.st_mode & S_IXUSR) && !(ret = 0))
		ft_fprintf(2, "cd: Permissions denied: %s\n", pa);
	ft_strdel(&fp);
	return (ret);
}

static int	f_cd_helper(t_mns *mns, char **cmd, char *pa)
{
	char		*old;

	if (chdir(pa) == -1)
	{
		ft_fprintf(2, "cd: : error on chdir functionr\n", pa);
		ft_strdel(&pa);
		return (0);
	}
	old = get_val(mns->envcpy, "PWD");
	set_val(mns->envcpy, "OLDPWD", ft_strdup(old));
	if (!(pa = getcwd(0, 0)))
	{
		ft_fprintf(2, "cd: : error on getcwd function\n", pa);
		ft_strdel(&pa);
		return (0);
	}
	set_val(mns->envcpy, "PWD", pa);
	if (!ft_strcmp(cmd[1], "-"))
		ft_printf("%s\n", get_val(mns->envcpy, "PWD"));
	return (1);
}

static char	**null_arg(t_mns *mns, char **cmd)
{
	char			***cmds;
	char			*hm;

	if (!(hm = get_val(mns->envcpy, "HOME")))
		return (0);
	cmds = mns->cmds;
	while (*cmds)
	{
		if (*cmds == cmd)
			break ;
		cmds++;
	}
	*cmds = ft_str_to_tab(cmd, ft_strdup(hm));
	return (*cmds);
}

int			f_cd(t_mns *mns, char **cmd)
{
	char		*pa;

	if (ft_strtablen(cmd) > 2)
	{
		ft_fprintf(2, "cd: Usage cd [DIR_PATH]\n");
		return (0);
	}
	if (!cmd[1] && !(cmd = null_arg(mns, cmd)))
		return (0);
	pa = cmd[1];
	if (!ft_strcmp(pa, "-"))
		if (!(pa = get_val(mns->envcpy, "OLDPWD")))
			return (0);
	if (!is_valid_dir(mns, pa))
		return (0);
	if (!f_cd_helper(mns, cmd, pa))
		return (0);
	return (1);
}
