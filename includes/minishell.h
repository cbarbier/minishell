/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 22:26:25 by cbarbier          #+#    #+#             */
/*   Updated: 2017/10/10 15:14:43 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define DEBUG				0
# define NB_BLTNS			6
# define BLTN_NAME_LENGTH	15
# include "../libft/includes/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <signal.h>

typedef struct				s_parser
{
	int			dq;
	int			q;
	int			ret;
	int			sv;
}							t_parser;
struct s_mns;
typedef struct				s_bltin
{
	char			name[BLTN_NAME_LENGTH];
	int				(*f)(struct s_mns *, char **, char **);
}							t_bltin;
typedef struct				s_mns
{
	char			**keys;
	char			**envcpy;
	char			**paths;
	t_bltin			bltins[NB_BLTNS];
	char			***cmds;
	char			***tcmds;
	int				status;
	char			*err;
	int				run;
}							t_mns;
int							init_mns(t_mns *mns, char **env);
void						line_reader(t_mns *mns, const int fd);
int							treat_cmd(t_mns *mns, char ***a_cmd, char **env);
int							try_cmd(t_mns *mns, char *fp, char **cmd);
int							exec_cmd(t_mns *m, char *p, char **c, char **e);
int							found_cmd(char *path, char *cmd);
int							parse_token(t_mns *mns, char ***cmds);
char						*get_val(char **tab, const char *key);
int							set_val(char **tab, const char *key, char *val);
int							maj_keys(t_mns *mns);
void						free_mns(t_mns *mns);
void						free_mns_cmds(t_mns *mns);
int							f_cd(t_mns *mns, char **cmd, char **env);
int							f_echo(t_mns *mns, char **cmd, char **env);
int							f_exit(t_mns *mns, char **cmd, char **env);
int							f_env(t_mns *mns, char **cmd, char **env);
int							f_setenv(t_mns *mns, char **cmd, char **env);
int							f_unsetenv(t_mns *mns, char **cmd, char **env);

#endif
