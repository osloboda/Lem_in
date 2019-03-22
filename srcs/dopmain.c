/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dopmain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:33:40 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/13 15:33:55 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int			stend(t_var **var, t_map **map, t_bist **lins, char *line)
{
	if (!ft_strcmp("##start", line))
	{
		if (startend(&line, &*map, &(*var)->start, &(*lins)))
			return (error(line, *var, *map, *lins) + 1);
	}
	else if (!ft_strcmp("##end", line))
	{
		if (startend(&line, &*map, &(*var)->end, &(*lins)))
			return (error(line, *var, *map, *lins) + 1);
	}
	else if (!ft_strcmp("##pin", line))
	{
		if (startend(&line, &*map, &(*var)->pinned, &(*lins)))
			return (error(line, *var, *map, *lins) + 1);
	}
	else if (!ft_strcmp("##lock", line))
	{
		if (startend(&line, &*map, &(*var)->locked, &(*lins)))
			return (error(line, *var, *map, *lins) + 1);
	}
	else
		return (3);
	return (1);
}

int			parseinf(t_var **var, t_map **map, t_bist **lins, char *line)
{
	int		flag;

	flag = 3;
	if (*line != '#')
	{
		flag = 1;
		if (ft_strchr(line, '-') && !ft_strchr(ft_strchr(line,
				'-') + 1, '-') && !ft_strchr(line, ' '))
		{
			if (push_links(*map, *map, ft_strsplit(line, '-')))
				return (error(line, (*var), *map, *lins) + 1);
			ftlstadd(&(*lins), ftlstnew(line, sizeof(t_bist)));
		}
		else if (!ft_strchr(line, '-'))
		{
			if (!(*map = push_front(*map, line)))
				return (error(line, (*var), *map, *lins) + 1);
			ftlstadd(&(*lins), ftlstnew(line, sizeof(t_bist)));
		}
		else
			flag = error(line, (*var), *map, *lins) + 1;
	}
	return (flag);
}

void		reqcheck(t_var **var, t_bist **lins, char *line)
{
	if (!ft_strncmp(REQ, line, 39))
	{
		(*var)->req = ft_atoi(line + 39);
		ftlstadd(&(*lins), ftlstnew(line, sizeof(t_bist)));
	}
	else
		ftlstadd(&(*lins), ftlstnew(line, sizeof(t_bist)));
}

int			startmar(t_var **var, t_map **map, char *line, t_bist **lins)
{
	int		i;

	if (!(*var)->start || !(*var)->end)
		return (error(NULL, *var, *map, *lins));
	i = 1;
	(*var)->ways = NULL;
	line = NULL;
	while (bfs2((*var), i, 0, 0) && i++)
		store_way(*var, (*var)->end, (*var)->ways, 0);
	if ((*var)->ways)
	{
		lines(*lins, 1);
		marafon(*var);
	}
	else
		return (error(line, *var, *map, *lins));
	return (0);
}

int			dopmain(t_var **var, t_map **map, t_bist **lins)
{
	char	*line;
	int		flag;

	while (get_next_line(0, &line) && line && *line)
	{
		flag = stend(&(*var), &(*map), &(*lins), line);
		if (flag == 2)
			return (1);
		else if (flag == 1)
			continue ;
		else if ((!ft_strchr(line, ' ') || !ft_strchr(ft_strchr(line,
				' ') + 1, ' ') || ft_strchr(ft_strchr(ft_strchr(line,
						' ') + 1, ' ') + 1, ' ')) && !ft_strchr(line,
								'-') && *line != '#')
			return (error(line, (*var), *map, *lins));
		flag = parseinf(&(*var), &(*map), &(*lins), line);
		if (flag == 2)
			return (1);
		else if (flag == 1)
			continue ;
		else
			reqcheck(&(*var), &(*lins), line);
		line = NULL;
	}
	return (startmar(&(*var), &(*map), line, &(*lins)));
}
