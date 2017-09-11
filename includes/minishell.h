/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 16:13:43 by cbarbier          #+#    #+#             */
/*   Updated: 2017/08/24 14:54:45 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define NB_BLTNS	6
# define BLTN_NAME_LENGTH	15
#include "../libft/includes/libft.h"

typedef	struct	s_venv
{
	char		*name;
	char		*value;
}				t_venv;
typedef struct	s_cmd
{
	char		*path;
	char		**args;
}				t_cmd;
typedef struct	s_mns		t_mns;
typedef struct 	s_bltin
{
	char		name[BLTN_NAME_LENGTH];
	int			(*f)(t_mns *mns, t_cmd *cmd);
}				t_bltin;
typedef struct	s_mns
{
	char		*prompt;
	t_venv		*env;
	char		**envcpy;
	char		**paths;
	t_bltin		bltins[NB_BLTNS];
	char		*line;
	t_list		*cmds;
}				t_mns;
int			init_mns(t_mns *mns, char **env);
int			compute_cmd(t_mns *mns, int *run);
char			**line_reader(const int fd);


int			f_cd(t_mns *mns, t_cmd *cmd);
int			f_echo(t_mns *mns, t_cmd *cmd);
int			f_exit(t_mns *mns, t_cmd *cmd);
int			f_env(t_mns *mns, t_cmd *cmd);
int			f_setenv(t_mns *mns, t_cmd *cmd);
int			f_unsetenv(t_mns *mns, t_cmd *cmd);
#endif
