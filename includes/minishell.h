/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 22:26:25 by cbarbier          #+#    #+#             */
/*   Updated: 2017/09/13 16:54:53 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define NB_BLTNS			6
# define BLTN_NAME_LENGTH	15
# include "../libft/includes/libft.h"
# include <dirent.h>
# include <sys/stat.h>

typedef	struct s_mns		t_mns;
typedef	struct				s_bltin
{
	char			name[BLTN_NAME_LENGTH];
	int				(*f)(t_mns *, char **);
}							t_bltin;
typedef struct				s_mns
{
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
int							treat_cmd(t_mns *mns, char ***a_cmd);
int							parse_token(t_mns *mns, char ***cmds);
char						*get_val(char **tab, const char *key);
int							set_val(char **tab, const char *key, char *val);
void						sig_handler(int s);
void						free_mns(t_mns *mns);
void						free_mns_cmds(t_mns *mns);
int							f_cd(t_mns *mns, char **cmd);
int							f_echo(t_mns *mns, char **cmd);
int							f_exit(t_mns *mns, char **cmd);
int							f_env(t_mns *mns, char **cmd);
int							f_setenv(t_mns *mns, char **cmd);
int							f_unsetenv(t_mns *mns, char **cmd);

#endif
