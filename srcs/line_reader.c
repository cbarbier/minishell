/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:43:05 by cbarbier          #+#    #+#             */
/*   Updated: 2017/08/24 14:48:44 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	its_the_end(char c, int *quote, int *dquote)
{
	int		ret;

	ret = 0;
	if (c == ' ' || c == '\t')
		ret = !*quote && !*dquote ? 1 : 0;
	else if (c == '"')
	{
		*dquote = *dquote ? 0 : 1;
		quote = 0;
		ret = !*dquote;
	}
	else if (c == '\'')
	{
		*quote = *quote ? 0 : 1;
		*dquote = 0;
		ret = !*quote;
	}
	else
		ret = c == '\n' && (!*dquote && !*quote) ? -1 : 0;
	return (ret);
}

char		**line_reader(const int fd)
{
	int		quote;
	int		dquote;
	char		c[2];
	char		**tab;
	char		*token;
	int		ret;

	quote = 0;
	dquote = 0;
	tab = 0;
	c[1] = 0;
	token = 0;
	while (read(fd, c, 1) > 0)
	{
		if ((ret = its_the_end(c[0], &quote, &dquote)) < 0)
			return (tab);
		else if (!ret)
		{
			ft_printf("\nend token %s\n", token);
			if (token)
			{
				tab = ft_str_to_tab(tab, token);
				token = 0;
			}
		}
		else
		{
			ft_printf("\nno end token %s\n", token);
			if (c[0] == '\n')
				ft_printf("$>");
			token = ft_strjoinzfree(token, c, 1); 
		}
	}
	return (tab);
}
