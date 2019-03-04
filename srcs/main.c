/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 13:05:04 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/04 13:07:54 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		free_mass(char **mass)
{
	free(mass[2]);
	free(mass[1]);
	free(mass);
}

void		push_front(t_map *head, char *line)
{
	char 	**mass;
	t_map	*tmp;

	mass = ft_strsplit(line, ' ');
	tmp = (t_map*) malloc(sizeof(t_map));
	tmp->next  = head->next;
	tmp->x = head->x;
	tmp->y = head->y;
	tmp->name = head->name;
	tmp->link = NULL;
	head->name = mass[0];
	head->x = ft_atoi(mass[1]);
	head->y = ft_atoi(mass[2]);
	head->next  = tmp;
	head->link = NULL;
	free_mass(mass);
}

void			find_dest(t_map *cur, t_map *head, char *n)
{
	t_rst		*tmp;
	t_map		*tmp2;

	tmp2 = head;
	tmp = cur->link;
	while (tmp)
	{
		tmp = tmp->next;
	}
	while (tmp2)
	{
		if (!(ft_strcmp(tmp2->name, n)))
			break ;
		tmp2 = tmp2->next;
	}
	tmp = (t_rst*)malloc(sizeof(t_rst));
	tmp->room = tmp2;
	tmp2->link = cur;
}

void		push_links(t_map *head, char *line)
{
	t_map	*tmp;
	char	**mass;

	mass = ft_strsplit(line, '-');
	tmp = head;
	while (tmp->next)
	{
		if (!(ft_strcmp(tmp->name, mass[0])))
		{
			find_dest(tmp, head, mass[1]);
			free(mass[0]);
			free(mass[1]);
			free(mass);
		}
		tmp = tmp->next;
	}
}

int			main(void)
{
	t_var	*var;
	t_map	*map;
	char	*line;

	var = malloc(sizeof(t_var));
	map = malloc(sizeof(t_var));
	get_next_line(0, &line);
	if (ft_atoi(line) > 0)
	{
		var->ants = ft_atoi(line);
		ft_strdel(&line);
		while (get_next_line(0, &line))
		{
			if (!ft_strcmp("##start", line))
			{
				ft_strdel(&line);
				get_next_line(0, &line);
				push_front(map, line);
				var->start = map;
			}
			else if (!ft_strcmp("##end", line))
			{
				ft_strdel(&line);
				get_next_line(0, &line);
				push_front(map, line);
				var->end = map;
			}
			else if (ft_isdigit(*line))
			{
				if (ft_strchr(line, '-'))
					push_links(map, line);
				else
					push_front(map, line);
			}
			ft_strdel(&line);
		}
	}
	else
	{
		ft_strdel(&line);
		ft_printf("ERROR\n");
	}
	free(var);
	free(map);
	return (0);
}
