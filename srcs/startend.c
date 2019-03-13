/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startend.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:34:53 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/13 15:34:55 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_rst		*find_dest(t_map *cur, t_map *head, char *n)
{
	t_rst	*tmp;
	t_map	*tmp2;

	tmp2 = head;
	tmp = NULL;
	while (tmp2)
	{
		if (!(ft_strcmp(tmp2->name, n)))
			break ;
		tmp2 = tmp2->next;
	}
	if (!tmp2)
		return (tmp);
	dop_dest(tmp, tmp2, &cur);
	return (cur->link);
}

int			push_links(t_map *head, t_map *tmp, char **mass)
{
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, mass[0]))
		{
			if (!(tmp->link = find_dest(tmp, head, mass[1])))
				return (freem(mass));
			break ;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		return (freem(mass));
	tmp = head;
	while (tmp)
	{
		if (!(ft_strcmp(tmp->name, mass[1])))
		{
			tmp->link = find_dest(tmp, head, mass[0]);
			break ;
		}
		tmp = tmp->next;
	}
	freem(mass);
	return (0);
}

t_map		*take_back(t_map *map)
{
	t_map	*tmp;

	tmp = map;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void		lines(t_bist *lines, int flag)
{
	t_bist	*tmp;
	t_bist	*tmp2;

	tmp = lines;
	if (tmp)
		tmp = tmp->next;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (flag)
			ft_printf("%s\n", tmp->content);
		free(tmp->content);
		free(tmp);
		tmp = tmp2;
	}
	if (flag)
		ft_printf("\n");
}

int			startend(char **line, t_map **map, t_map **dest, t_bist **lins)
{
	if (*dest)
		return (1);
	ftlstadd(&(*lins), ftlstnew(*line, sizeof(t_bist)));
	while (get_next_line(0, &(*line)) && **line == '#' && ft_strcmp(*line,
			"##start") && ft_strcmp(*line, "##end") &&
		ft_strcmp(*line, "##pin") && ft_strcmp(*line, "##lock"))
		ftlstadd(&(*lins), ftlstnew(*line, sizeof(t_bist)));
	if ((!ft_strchr(*line, ' ') || !ft_strchr(ft_strchr(*line, ' ') + 1, ' ')
		|| ft_strchr(ft_strchr(ft_strchr(*line, ' ') + 1, ' ') + 1, ' ')))
		return (1);
	if (!(*map = push_front(*map, *line)))
		return (1);
	ftlstadd(&(*lins), ftlstnew(*line, sizeof(t_bist)));
	*dest = take_back(*map);
	return (0);
}
