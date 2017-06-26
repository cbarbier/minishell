/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 16:13:43 by cbarbier          #+#    #+#             */
/*   Updated: 2017/06/26 18:19:56 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define NB_BLTNS	6
# define BLTN_NAME_LENGTH	15
#include "../libft/includes/libft.h"

typedef	struct	s_envv
{
	char		*name;
	char		*value;
}				t_venv;
typedef struct 	s_bltin
{
	char		name[BLTN_NAME_LENGTH];
	int			(*f)(char *cmd);
}				t_bltin;
typedef struct	s_mns
{
	char		*prompt;
	t_venv		*env;
	t_bltin		bltins[NB_BLTNS];
	char		*line;
}				t_mns;
#endif
