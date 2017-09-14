/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:43:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/09/14 16:53:16 by cbarbier         ###   ########.fr       */
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

static int	parse_char(char *c, t_parser *p)
{
	p->sv = p->ret;
	p->ret = 0;
	if (*c == ';')
		p->ret = !p->q && !p->dq ? 2 : 0;
	if (*c == ' ' || *c == '\t')
		p->ret = !p->q && !p->dq ? 1 : 0;
	else if (*c == '"' && !p->q)
	{
		p->ret = p->q && !p->sv ? 1 : 0;
		p->dq = p->dq ? 0 : 1;
	}
	else if (*c == '\'' && !p->dq)
	{
		p->ret = !p->dq && !p->sv ? 1 : 0;
		p->q = p->q ? 0 : 1;
	}
	if (!DEBUG)
		return (p->ret);
	ft_printf("%c {q:%d dq:%d ret:%d sv:%d}\n", *c, p->q, p->dq, p->ret, p->sv);
	return (p->ret);
}

static int	to_cat(t_parser *p, char c)
{
	(void)c;
	if (p->ret == 2)
		return (0);
	if (c == '"')
		return (p->q ? 1 : 0);
	if (c == '\'')
		return (p->dq ? 1 : 0);
	if (p->ret == 1)
		return (0);
	if (p->ret == 0)
		return (1);
	return (0);
}

static int	tokenize(t_mns *mns, char *line, t_parser *p, char **a_token)
{
	char		*token;

	token = *a_token;
	while (*line)
	{
		parse_char(line, p);
		if (to_cat(p, *line))
			token = ft_strnjoinzfree(token, line, 1, 1);
		if (p->ret && token)
		{
			*mns->tcmds = ft_str_to_tab(*mns->tcmds, token);
			token = 0;
		}
		if (p->ret == 2)
			add_new_cmd(mns);
		line++;
	}
	if (p->q || p->dq)
		*a_token = ft_strnjoinzfree(token, "\n", 1, 1);
	else if (token)
		*mns->tcmds = ft_str_to_tab(*mns->tcmds, token);
	return (!p->q && !p->dq);
}

void		line_reader(t_mns *mns, const int fd)
{
	char		*line;
	char		*token;
	int			ret;
	t_parser	parser;

	token = 0;
	ft_bzero(&parser, sizeof(t_parser));
	while (get_next_line(fd, &line) >= 0)
	{
		ret = tokenize(mns, line, &parser, &token);
		ft_strdel(&line);
		if (ret)
			break ;
		ft_printf((parser.dq ? "$dq>" : "$q>"));
	}
}
