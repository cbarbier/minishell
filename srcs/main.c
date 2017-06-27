/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:43:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/06/27 19:16:04 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_strtab_pop(char **tab, int ipop)
{
	int		index;
	char	**tmp;

	index = 0;
	tmp = 0;
	while (tab[index])
	{
		tmp = tab + index;
		index++;
	}
	if (tmp)
		ft_strdel(tmp);
	return (1);
}

int			main(int argc, char **argv, char **envp)
{
	t_mns		mns;
	int			ret;
	char		*buf;
	char		**paths;
	char		**cmd;
	char		*tmp;
	int			ip;
	int 		status;
	int			cpid;
	char		**envcpy;

	(void)argv;
	(void)argc;
	envcpy = 0;
	ft_bzero(&mns, sizeof(t_mns));
	while (*envp)
	{
		ft_printf("%s\n", *envp);
		if (!ft_strncmp("PATH", *envp, 4))
		{
			paths = ft_strsplit((*envp) + 5, ':');
//			ft_putstrtab(paths);
		}
		envcpy = ft_str_to_tab(envcpy, *envp);
		envp++;
	}
	buf = getcwd(0, 0);
	ft_printf("cur path: %s\n", buf);
	while (1)
	{
		ft_printf("{blu}$>{no}");
		if ((ret = get_next_line(0, &(mns.line))) <= 0)
			break;
		cmd = ft_strsplit(mns.line, ' ');
		ip = 0;
		while (paths[ip])
		{
			tmp = ft_strjoin(paths[ip], "/");
			tmp = ft_strjoin(tmp, cmd[0]);
			//ft_printf("tmp = %s\n", tmp);
			if (!access(tmp, X_OK))
			{
				if ((cpid = fork()) < 0)
				{
					ft_printf("fork error");
					exit(1);
				}
				else if (cpid == 0)
				{
				//	ft_putstrtab(envcpy);
					execve(tmp, cmd, envcpy);
					exit(0);
				}
				else
				{
					waitpid(cpid, &status, 0);
					if (!status)
						ft_printf("child ok\n");
					else
						ft_printf("child ko\n");
				}
			}
			ip++;
		}
	}
	ft_printf("last ret = %d\n", ret);
	return (0);
}
