/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:37:01 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/13 15:37:06 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int			is_digit(char *line)
{
	char	*tmp;

	tmp = line;
	if (*tmp == '-')
		tmp++;
	while (tmp && *tmp)
		if (!ft_isdigit((int)*(tmp++)))
			return (0);
	return (1);
}

int			dop_push(t_map **tmp2, t_map *tmp, char **mass)
{
	(*tmp2) = (t_map*)malloc(sizeof(t_map));
	(*tmp2)->name = mass[0];
	(*tmp2)->x = ft_atoi(mass[1]);
	(*tmp2)->y = ft_atoi(mass[2]);
	(*tmp2)->next = NULL;
	(*tmp2)->prev = NULL;
	(*tmp2)->link = NULL;
	(*tmp2)->visited = 0;
	(*tmp2)->locked = 0;
	(*tmp2)->ant = 0;
	free_mass(mass);
	if (!tmp)
		return (1);
	else
		tmp->next = (*tmp2);
	return (0);
}

t_map		*push_front(t_map *head, char *line)
{
	char	**mass;
	t_map	*tmp;
	t_map	*tmp2;

	tmp = head;
	mass = ft_strsplit(line, ' ');
	if (!is_digit(mass[1]) || !is_digit(mass[2]) || ft_strchr(mass[0], '-'))
	{
		free_mass(mass);
		return (0);
	}
	while (tmp && tmp->next && tmp->name != mass[0] && (tmp->x !=
		ft_atoi(mass[1]) || tmp->y != ft_atoi(mass[2])))
		tmp = tmp->next;
	if (tmp && (!ft_strcmp(tmp->name, mass[0]) || (tmp->x ==
		ft_atoi(mass[1]) && tmp->y == ft_atoi(mass[2]))))
	{
		free_mass(mass);
		return (0);
	}
	if (dop_push(&tmp2, tmp, mass))
		return (tmp2);
	return (head);
}

void		dop_dest(t_rst *tmp, t_map *tmp2, t_map **cur)
{
	if (!(*cur)->link)
	{
		(*cur)->link = (t_rst*)malloc(sizeof(t_rst));
		tmp = (*cur)->link;
		tmp->room = tmp2;
		tmp->next = NULL;
	}
	else
	{
		tmp = (t_rst *)malloc(sizeof(t_rst));
		tmp->next = (*cur)->link->next;
		tmp->room = tmp2;
		(*cur)->link->next = tmp;
	}
}

int			freem(char **mass)
{
	free(mass[0]);
	free(mass[1]);
	free(mass);
	return (1);
}
