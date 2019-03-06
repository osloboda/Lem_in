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

void		freelst(t_var *var, t_map *map)
{
	t_map	*m;
	t_map	*tmp;
	t_rst	*t;

	m = map;
	free(var);
	while (m)
	{
		tmp = m->next;
		free(m->name);
		while (m->link)
		{
			t = m->link->next;
			free(m->link);
			m->link = t;
		}
		free(m);
		m = tmp;
	}
}

int        error(char *line, t_var *var, t_map *map)
{
	ft_strdel(&line);
	ft_printf("ERROR\n");
	freelst(var, map);
	return (0);
}

int			is_digit(char *line)
{
	char	*tmp;

	tmp = line;
	while (tmp && *tmp)
		if (!ft_isdigit((int)*(tmp++)))
			return (0);
	return (1);
}

void		lstadd(t_li **alst, t_li *new)
{
	t_li	*tmp;

	if (alst != NULL && new != NULL)
	{
		tmp = *alst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_li		*lstnew(t_map *content, size_t content_size)
{
	t_li	*t;

	if (!(t = (t_li*)malloc(sizeof(t_li))))
		return (NULL);
	if (content != NULL)
	{
		t->content = content;
		t->content_size = content_size;
	}
	else
	{
		t->content = NULL;
		t->content_size = 0;
	}
	t->next = NULL;
	return (t);
}


void		BFS(t_map *c, t_var *var)
{
    t_map		*v;
	t_rst		*tmp;
	t_li		*waiting;
	int 		flag;

	flag = 1;
	v = c;
	waiting = lstnew(v, sizeof(t_map*));
    while (waiting && waiting->content && flag)
	{
    	v = waiting->content;
    	waiting = waiting->next;
    	tmp = v->link;
    	v->visited = 1;
    	while (tmp)
		{
    		if (!tmp->room->visited)
    		{
    			if (!waiting)
    				waiting = lstnew(tmp->room, sizeof(t_map*));
    			else
    				lstadd(&waiting, lstnew(tmp->room, sizeof(t_map*)));
				tmp->room->prev = v;
			}
    		tmp = tmp->next;
		}
	}
    var->ants = var->ants;
}

t_map		*push_front(t_map *head, char *line)
{
	char 	**mass;
	t_map	*tmp;
    t_map	*tmp2;

	tmp = head;
	tmp2 = NULL;
	mass = ft_strsplit(line, ' ');
	if (!is_digit(mass[1]) || !is_digit(mass[2]))
	{
		free_mass(mass);
		return (tmp2);
	}
	while (tmp && tmp->next && tmp->name != mass[0])
	    tmp = tmp->next;
	if (tmp && !ft_strcmp(tmp->name, mass[0]))
	{
		free_mass(mass);
		return (0);
	}
	tmp2 = (t_map*) malloc(sizeof(t_map));
    tmp2->name = mass[0];
    tmp2->x = ft_atoi(mass[1]);
    tmp2->y = ft_atoi(mass[2]);
    tmp2->next = NULL;
    tmp2->link = NULL;
    tmp2->visited = 0;
	free_mass(mass);
    if (!tmp)
        return (tmp2);
    else
    	tmp->next  = tmp2;
    return (head);
}

t_rst		*find_dest(t_map *cur, t_map *head, char *n)
{
	t_rst		*tmp;
	t_map		*tmp2;

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

int		push_links(t_map *head, char *line)
{
	t_map	*tmp;
	char	**mass;

	mass = ft_strsplit(line, '-');
	tmp = head;
	while (tmp)
	{
		if (!(ft_strcmp(tmp->name, mass[0])))
		{
			if (!(tmp->link = find_dest(tmp, head, mass[1])))
				return (1);
			break ;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		return (1);
	tmp = head;
	while (tmp)
	{
		if (!(ft_strcmp(tmp->name, mass[1])))
		{
			tmp->link = find_dest(tmp, head, mass[0]);
			free(mass[0]);
			free(mass[1]);
			free(mass);
			break ;
		}
		tmp = tmp->next;
	}
	return (0);
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

t_map		*take_back(t_map *map)
{
	t_map	*tmp;

	tmp = map;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

int			main(void)
{
	t_var	*var;
	t_map	*map;
	char	*line;
	int 	flag;

	flag = 1;
	var = malloc(sizeof(t_var));
	var->start = NULL;
    var->end = NULL;
    map = NULL;
	while (get_next_line(0, &line) && line && *line == '#')
		ft_strdel(&line);
	if (line && is_digit(line) && ft_atoi(line) > 0)
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
                if (((!ft_strchr(line, ' ') || !ft_strchr(ft_strchr(line, ' ') + 1, ' ') || ft_strchr(ft_strchr(ft_strchr(line, ' ') + 1, ' ') + 1, ' ')) || ft_strchr(line, '-')) && *line != '#')
                    return (error(line, var, map));
                map = push_front(map, line);
				var->start = take_back(map);
			}
			else if (!ft_strcmp("##end", line))
			{
                if (var->end)
                    return (error(line, var, map));
				ft_strdel(&line);
				while (get_next_line(0, &line) && *line == '#')
					ft_strdel(&line);
                if (((!ft_strchr(line, ' ') || !ft_strchr(ft_strchr(line, ' ') + 1, ' ') || ft_strchr(ft_strchr(ft_strchr(line, ' ') + 1, ' ') + 1, ' ')) || ft_strchr(line, '-')) && *line != '#')
                    return (error(line, var, map));
                map = push_front(map, line);
				var->end = take_back(map);
			}
			else if ((!ft_strchr(line, ' ') || !ft_strchr(ft_strchr(line, ' ') + 1, ' ') || ft_strchr(ft_strchr(ft_strchr(line, ' ') + 1, ' ') + 1, ' ')) && !ft_strchr(line, '-') && *line != '#')
                return (error(line, var, map));
			else if (*line != '#')
            {
                if (ft_strchr(line, '-') && !ft_strchr(ft_strchr(line, '-') + 1, '-') && !ft_strchr(line, ' ') && !(flag = 0))
				{
                	if (push_links(map, line))
						return (error(line, var, map));
				}
				else if (!ft_strchr(line, '-'))
				{
					if (!(map = push_front(map, line)))
						return (error(line, var, map));
				}
                else
                    return (error(line, var, map));
			}
			ft_strdel(&line);
		}
		if (!var->start || !var->end || flag)
            return (error(line, var, map));
        printlist(map);
	}
	else
        return (error(line, var, map));
	freelst(var, map);
	system("leaks lem-in");
	return (0);
}
