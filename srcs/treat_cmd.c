/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:43:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/10/10 15:30:24 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	try_bltins(t_mns *mns, char **cmd, char **env)
{
	int		i;

	i = 0;
	while (i < NB_BLTNS)
	{
		if (!ft_strcmp(cmd[0], mns->bltins[i].name))
			break ;
		i++;
	}
	if (i == NB_BLTNS)
		return (-1);
	mns->bltins[i].f(mns, cmd, env);
	return (i);
}

static char	*try_path(t_mns *mns, char **cmd)
{
	char		**path;
	char		*p;

	if (!(path = mns->paths))
		return (0);
	while (*path)
	{
		if (found_cmd(*path, cmd[0]))
		{
			p = ft_strjoin(*path, "/");
			p = ft_strnjoinzfree(p, cmd[0], ft_strlen(cmd[0]), 1);
			if (try_cmd(mns, p, cmd))
				return (p);
			ft_strdel(&p);
			break ;
		}
		path++;
	}
	return (0);
}

int			try_cmd(t_mns *mns, char *fp, char **cmd)
{
	struct stat		st;

	if (!ft_strchr("/.", *fp) || stat(fp, &st) == -1 || S_ISDIR(st.st_mode))
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

int			exec_cmd(t_mns *mns, char *path, char **cmd, char **env)
{
	int		cpid;
	int		status;
	int		ret;

	if ((cpid = fork()) < 0)
	{
		ft_fprintf(2, "fork error");
		return (0);
	}
	if (!cpid)
	{
		signal(SIGINT, SIG_DFL);
		ret = execve(path, cmd, env);
		ft_fprintf(2, "mns: error while executing: %s\n", path);
		exit(ret);
	}
	else
	{
		waitpid(cpid, &status, 0);
		if (WIFEXITED(status))
			mns->status = WEXITSTATUS(status);
	}
	return (1);
}

int			treat_cmd(t_mns *mns, char ***a_cmd, char **env)
{
	char		*p;
	char		**cmd;
	int			ret;

	mns->err = 0;
	cmd = *a_cmd;
	if (try_bltins(mns, cmd, env) >= 0)
		return (1);
	if ((p = try_path(mns, cmd)))
	{
		ret = exec_cmd(mns, p, cmd, env);
		ft_strdel(&p);
		return (ret);
	}
	if (try_cmd(mns, cmd[0], cmd))
		return (exec_cmd(mns, cmd[0], cmd, env));
	return (0);
}
