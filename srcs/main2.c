/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:43:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/08/24 14:48:44 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sig_handler(int sig)
{
	(void)sig;
	//ft_printf("signal caught %d\n", sig);
}

int			main(int argc, char **argv, char **envp)
{
	t_mns		mns;
	int		run;

	init_mns(&mns, envp);
	run = 1;
	signal(SIGINT, sig_handler);
	while (run)
	{
		ft_printf("{blu}$>{no}");
		if ((ret = get_next_line(0, &(mns.line))) <= 0)
			break;
		compute_cmd(&mns, &run);
		ft_strdel(&(mns.line));
	}
	return (0);
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

	signal(SIGINT, sig_handler);
	while (42)
	{
		ft_printf("{blu}$>{no}");
		if ((ret = get_next_line(0, &(mns.line))) <= 0)
			break;
		cmd = ft_strsplit(mns.line, ' ');
		ip = 0;
		if (!ft_strcmp(ft_strtrim(mns.line), "exit"))
			exit(0);
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
					signal(SIGINT, sig_handler);
					waitpid(cpid, &status, 0);
					if (!status)
						ft_printf("child ok\n");
					else
						ft_printf("child ko\n");
				}
				break;
			}
			ip++;
		}
	}
	ft_printf("last ret = %d\n", ret);
	return (0);
}
