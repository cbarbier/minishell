/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:43:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/09/12 22:14:19 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_new_cmd(t_mns *mns)
{
	int				len;
	int				i;
	char			***t;

	t = mns->cmds;
	len = 0;
	while (*t++)
		len++;
	if (!(t = (char ***)ft_memalloc((len + 2) * sizeof(char **))))
		return (0);
	i = -1;
	while (++i < len)
		t[i] = mns->cmds[i];
	free(mns->cmds);
	mns->cmds = t;
	mns->tcmds = t + i;
	return (1);
}

static int	its_the_end(char *c, int *quote, int *dquote)
{
	int		ret;

	ret = 0;
	if (*c == ';')
		ret = !*quote && !*dquote ? 2 : 0;
	if (*c == ' ' || *c == '\t')
		ret = !*quote && !*dquote ? 1 : 0;
	else if (*c == '"' && !*quote)
	{
		*dquote = *dquote ? 0 : 1;
		ret = *dquote ? 0 : 1;
		if (*dquote)
			ret = 1;
	}
	else if (*c == '\'' && !*dquote)
	{
		*quote = *quote ? 0 : 1;
		ret = *quote ? 0 : 1;
		if (*quote)
			ret = 1;
	}
	//ft_printf("%c q:%d dq:%d ret:%d\n", *c, *quote, *dquote, ret);
	return (ret);
}

static int	tokenize(t_mns *mns, char *line, int *qs, char **a_token)
{
	char		*token;
	char		ret;

	token = *a_token;
	while (*line)
	{
		if ((ret = its_the_end(line, qs, qs + 1)) && token)
		{
			*mns->tcmds = ft_str_to_tab(*mns->tcmds, token);
			token = 0;
		}
		else if (!ft_strchr("'\"", *line))
			token = ft_strnjoinzfree(token, line, 1, 1);
		if (ret == 2)
			add_new_cmd(mns);
		line++;
	}
	if (qs[0] || qs[1])
		*a_token = ft_strnjoinzfree(token, "\n", 1, 1);
	else if (token)
		*mns->tcmds = ft_str_to_tab(*mns->tcmds, token);
	return (!qs[0] && !qs[1]);
}

void		line_reader(t_mns *mns, const int fd)
{
	char		*line;
	char		*token;
	int			q[2];
	int			ret;

	token = 0;
	ft_bzero(q, 2 * sizeof(int));
	while (get_next_line(fd, &line) >= 0)
	{
		ret = tokenize(mns, line, q, &token);
		ft_strdel(&line);
		if (ret)
			break ;
		ft_printf("$>");
	}
}
