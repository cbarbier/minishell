/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:43:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/09/12 22:15:04 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	try_cmd(t_mns *mns, char *fp, char **cmd)
{
	ft_printf("try_cmd\n");
	if (access(fp, F_OK) == -1)
	{
		ft_strdel(&mns->err);
		ft_asprintf(&mns->err, "mnsh: command not found: %s\n", cmd[0]);
		return (0);
	}
	else if (access(fp, X_OK) == -1)
	{
		ft_strdel(&mns->err);
		ft_asprintf(&mns->err, "mnsh: permission denied: %s\n", cmd[0]);
		return (0);
	}
	ft_strdel(&mns->err);
	return (1);
}

static int	try_bltins(t_mns *mns, char **cmd)
{
	int		i;

	ft_printf("try_builtins\n");
	i = 0;
	while (i < NB_BLTNS)
	{
		if (!ft_strcmp(cmd[0], mns->bltins[i].name))
			break ;
		i++;
	}
	if (i == NB_BLTNS)
		return (-1);
	mns->bltins[i].f(mns, cmd);
	return (i);
}

static char	*try_path(t_mns *mns, char **cmd)
{
	char		**path;
	char		*p;

	ft_printf("try_path\n");
	path = mns->paths;
	while (*path)
	{
		if ((*path)[ft_strlen(*path) - 1] != '/')
			p = ft_strjoin(*path, "/");
		else
			p = ft_strdup(*path);
		p = ft_strnjoinzfree(p, cmd[0], ft_strlen(cmd[0]), 1);
		if (try_cmd(mns, p, cmd))
			return (p);
		ft_printf("p = %s\n", p);
		ft_strdel(&p);
		path++;
	}
	return (0);
}

static int	exec_cmd(t_mns *mns, char *path, char **cmd)
{
	int		cpid;

	if ((cpid = fork()) < 0)
	{
		ft_fprintf(2, "fork error");
		return (0);
	}
	if (!cpid)
	{
		execve(path, cmd, mns->envcpy);
		exit(0);
	}
	else
	{
		signal(SIGINT, sig_handler);
		waitpid(cpid, &mns->status, 0);
	}
	return (1);
}

int			treat_cmd(t_mns *mns, char ***a_cmd)
{
	char		*p;
	char		**cmd;
	int			ret;

	mns->err = 0;
	cmd = *a_cmd;
	if (try_bltins(mns, cmd) >= 0)
	{
		ft_printf("trying bltins\n");
		return (1);
	}
	if ((p = try_path(mns, cmd)))
	{
		ft_printf("trying path\n");
		ret = exec_cmd(mns, p, cmd);
		ft_strdel(&p);
		return (ret);
	}
	if (try_cmd(mns, cmd[0], cmd))
	{
		ft_printf("trying direct cmd\n");
		return (exec_cmd(mns, cmd[0], cmd));
	}
	return (0);
}
