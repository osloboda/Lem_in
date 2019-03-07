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

void		lstadd(t_li **alst, t_li *new)
{
	t_li	*tmp;

	if (alst != NULL && new != NULL)
	{
		tmp = *alst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
		tmp->next->prev = tmp;
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
	t->prev = NULL;
	return (t);
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

void		BFS(t_var *var, int unic)
{
	t_map		*v;
	t_rst		*tmp;
	t_li		*waiting;

	v = var->start;
	var->end->prev = NULL;
	waiting = lstnew(v, sizeof(t_map*));
	while (waiting && waiting->content && ft_strcmp(v->name, var->end->name))
	{
		v = waiting->content;
		waiting = waiting->next;
		tmp = v->link;
		v->visited = unic;
		while (tmp)
		{
			if (tmp->room->visited != unic && !tmp->room->locked)
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

void		store_way(t_var *var)
{
	t_li	*w;
	t_li	*tmp;
	t_map	*going;
	int 	i;

	w = var->ways;
	i = 0;
	going = var->end;
	while (w && w->next)
		w = w->next;
	if (!w)
	{
		var->ways = lstnew(0, sizeof(t_li *));
		w = var->ways;
	}
	else
		{
		lstadd(&w, lstnew(0, sizeof(t_li *)));
		w = w->next;
	}
	w->way = lstnew(going, sizeof(t_map *));
	while (going->prev && ++i)
	{
		if (ft_strcmp(going->prev->name, var->start->name))
			going->prev->locked = 1;
		tmp = lstnew(going->prev, sizeof(t_map *));
		tmp->next = w->way;
		w->way->prev = tmp;
		w->way = tmp;
		going = going->prev;
	}
	w->way->way_lenght = i;
}

int 		connn(t_li *tmp, t_li *ww)
{
	t_li	*www;
	int 	res;

	res = 0;
	www = ww;
	while (www && www->way != tmp)
	{
		res += tmp->way_lenght - www->way->way_lenght;
		www = www->next;
	}
	return (res);
}

int			mvway(t_li *cur, int i)
{
	t_li	*tmp;
	int 	r;

	tmp = cur;
	r = 0;
	while (tmp->next)
		tmp = tmp->next;
	tmp->content->ant = 0;
	while (tmp->prev && tmp->content->ant != i) {
		if (tmp->prev->content->ant) {
			tmp->content->ant = tmp->prev->content->ant;
			r = ft_printf("L%i-%s ", tmp->prev->content->ant, tmp->content->name);
			tmp->prev->content->ant = 0;
		}
		tmp = tmp->prev;
	}
	return (r);
}

void		marafon(t_var *var)
{
	t_li	*www;
	t_li	*tmp;
	int 	i;
	int 	lines;
	int		r;

	i = var->ants;
	lines = 0;
	r = 1;
	while (r)
	{
		tmp = var->ways;
		r = 0;
		while (tmp && (www = tmp->way->next))
		{
			www->way_lenght = tmp->way->way_lenght;
			r = mvway(www, var->ants - i);
			if ((www == var->ways->way && i > 0))
			{
				r = ft_printf("L%i-%s ", var->ants - i + 1, www->content->name);
				www->content->ant = var->ants - i + 1;
				i--;
			}
			else if (i > connn(tmp->way, var->ways))
			{
				r = ft_printf("L%i-%s ", var->ants - i + 1, www->content->name);
				www->content->ant = var->ants - i + 1;
				i--;
			}
			tmp = tmp->next;
		}
		ft_printf("\n");
		lines++;
	}
	ft_printf("%i\n", lines);
}

int			error(char *line, t_var *var, t_map *map)
{
	int i;
	i = 1;
	BFS(var, i);
	var->ways = NULL;
	var->start->prev = NULL;
	store_way(var);
	while (var->end->prev && i++)
	{
		BFS(var, i);
		if (!var->end->prev)
			break;
		store_way(var);
	}
	marafon(var);
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
	tmp2->locked = 0;
	tmp2->ant = 0;
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
