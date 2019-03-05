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


t_map		*push_front(t_map *head, char *line)
{
	char 	**mass;
	t_map	*tmp;
    t_map	*tmp2;

	tmp = head;
	while (tmp && tmp->next)
	    tmp = tmp->next;
    tmp2 = (t_map*) malloc(sizeof(t_map));
    mass = ft_strsplit(line, ' ');
    tmp2->name = mass[0];
    tmp2->x = ft_atoi(mass[1]);
    tmp2->y = ft_atoi(mass[2]);
    tmp2->next = NULL;
    tmp2->link = NULL;
    if (!tmp)
        return (tmp2);
    else
    	tmp->next  = tmp2;
	free_mass(mass);
    return (head);
}

t_rst		*find_dest(t_map *cur, t_map *head, char *n)
{
	t_rst		*tmp;
	t_map		*tmp2;

	tmp2 = head;
	while (tmp2)
	{
		if (!(ft_strcmp(tmp2->name, n)))
			break ;
		tmp2 = tmp2->next;
	}
	if (!cur->link)
	{
		cur->link = (t_rst*)malloc(sizeof(t_rst));
		tmp = cur->link;
        tmp->room = tmp2;
        tmp->next = NULL;
	}
	else
	    {
        tmp = (t_rst *) malloc(sizeof(t_rst));
        tmp->next = cur->link->next;
        tmp->room = tmp2;
        cur->link->next = tmp;
    }
	return (cur->link);
}

void		push_links(t_map *head, char *line)
{
	t_map	*tmp;
	char	**mass;

	mass = ft_strsplit(line, '-');
	tmp = head;
	while (tmp)
	{
		if (!(ft_strcmp(tmp->name, mass[0])))
		{
			tmp->link = find_dest(tmp, head, mass[1]);
			free(mass[0]);
			free(mass[1]);
			free(mass);
			break ;
		}
		tmp = tmp->next;
	}
}

void		printlist(t_map *map)
{
	t_map *tmp;

	tmp = map;
	while (tmp)
	{
	    if (tmp->link && tmp->link->next)
			ft_printf("%s %s %s\n", tmp->name, tmp->link->room->name, tmp->link->next->room->name);
		else if (tmp->link)
			ft_printf("%s %s\n", tmp->name, tmp->link->room->name);
		tmp = tmp->next;
	}
}

int        error(char *line, t_var	*var, t_map	*map)
{
    ft_strdel(&line);
    ft_printf("ERROR\n");
    printlist(map);
    free(var);
    if (map)
        free(map);
    return (0);
}

int			main(void)
{
	t_var	*var;
	t_map	*map;
	char	*line;

	var = malloc(sizeof(t_var));
	var->start = NULL;
    var->end = NULL;
	get_next_line(0, &line);
	if (ft_atoi(line) > 0)
	{
		var->ants = ft_atoi(line);
		ft_strdel(&line);
		while (get_next_line(0, &line))
		{
			if (!ft_strcmp("##start", line))
			{
			    if (var->start)
			        return (error(line, var, map));
			    ft_strdel(&line);

				while (get_next_line(0, &line) && *line == '#')
				    ft_strdel(&line);
                map = push_front(map, line);
				var->start = map;
			}
			else if (!ft_strcmp("##end", line))
			{
                if (var->end)
                    return (error(line, var, map));
				ft_strdel(&line);
				get_next_line(0, &line);
                map = push_front(map, line);
				var->end = map;
			}
			else if ((!ft_strchr(line, ' ') || !ft_strchr(ft_strchr(line, ' ') + 1, ' ') || ft_strchr(ft_strchr(ft_strchr(line, ' ') + 1, ' ') + 1, ' ')) && !ft_strchr(line, '-'))
                return (error(line, var, map));
			else if (*line != '#')
            {
			    if (ft_strchr(line, '-'))
					push_links(map, line);
				else
                    map = push_front(map, line);
			}
			ft_strdel(&line);
		}
		if (!var->start || !var->end)
            return (error(line, var, map));
	}
	else
        return (error(line, var, map));
	free(var);
	free(map);
	return (0);
}
