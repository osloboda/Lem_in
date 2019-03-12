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

	if (*alst != NULL && new != NULL)
	{
		tmp = *alst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
		tmp->next->prev = tmp;
	}
	else
		*alst = new;
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

void		freevar(t_var *var)
{
	t_li    *r;
	t_li    *b;
	t_li    *bb;

	if (var->ways)
	{
		r = var->ways;
		while (r)
		{
			b = r->way;
			while (b)
			{
				bb = b->next;
				free(b);
				b = bb;
			}
			bb = r->next;
			free (r);
			r = bb;
		}
	}
	free(var);
}

void		freelst(t_var *var, t_map *map)
{
	t_map	*m;
	t_map	*tmp;
	t_rst	*t;

	m = map;
	freevar(var);
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

void		store_way(t_var *var, t_map *going, t_li *w, int i)
{
	t_li	*tmp;

	lstadd(&w, lstnew(0, sizeof(t_li *)));
	var->ways = w;
	while (w && w->next)
		w = w->next;
	w->way = lstnew(going, sizeof(t_map *));
	while (going && going->prev && ++i)
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

int			connn(t_li *tmp, t_li *ww)
{
	t_li	*www;
	int		res;

	res = 0;
	www = ww;
	while (www && www->way != tmp)
	{
		res += tmp->way_lenght - www->way->way_lenght;
		www = www->next;
	}
	return (res);
}

int			mvway(t_li *cur, int i, int d, t_var *var)
{
	t_li	*tmp;
	int		flag;

	flag = 0;
	tmp = cur;
	while (tmp->next)
		tmp = tmp->next;
	tmp->content->ant = 0;
	while (tmp->prev && tmp->content->ant != i)
	{
		if (tmp->prev->content->ant)
		{
			tmp->content->ant = tmp->prev->content->ant;
			if (tmp->content != var->pinned)
				ft_printf(MAGENTA("L%i-%s "), tmp->prev->content->ant,
						  tmp->content->name);
			else
				ft_printf(CYAN("L%i-%s "), tmp->prev->content->ant,
					tmp->content->name);
			flag = 1;
			tmp->prev->content->ant = 0;
		}
		tmp = tmp->prev;
	}
	return ((d == 1) ? d : flag);
}

int		print_moves(t_var *var, int flag, int *i, t_li *www)
{
	t_li	*tmp;

	tmp = var->ways;
	while (tmp && (www = tmp->way->next))
	{
		www->way_lenght = tmp->way->way_lenght;
		flag = mvway(www, var->ants - *i, flag, var);
		if (*i > 0 && *i > connn(tmp->way, var->ways) && (flag = 1))
		{
			if (www->content == var->pinned)
				ft_printf(CYAN("L%i-%s "), var->ants - *i + 1, www->content->name);
			else
				ft_printf(BMAGENTA("L%i-%s "), var->ants - *i + 1, www->content->name);
			www->content->ant = var->ants - *i + 1;
			(*i)--;
		}
		tmp = tmp->next;
	}
	if (www && www->content != var->end && flag)
	{
		ft_putstr("\n");
		var->lines++;
	}
	return (flag);
}

void		marafon(t_var *var)
{
	int		i;
	int		flag;

	flag = 1;
	i = var->ants;
	var->lines = 1;
	while (i > 0 || flag || var->end->ant)
		flag = print_moves(var, 0, &i, 0);
	if (var->lines == 1)
		ft_putstr("\n");
	else
		var->lines -= 1;
}

t_map		*pop_queue(t_li **queue)
{
	t_li	*last;
	t_map	*room;

	room = NULL;
	if (*queue)
		room = (*queue)->content;
	last = *queue;
	(*queue) = (*queue)->next;
	free(last);
	return (room);
}

void		queuefree(t_li *wait)
{
	t_li	*tmp;

	while (wait)
	{
		tmp = wait->next;
		free(wait);
		wait = tmp;
	}
}

int 		dop_bfs(t_var *data, int uniq_bfs, t_li **queue)
{
	if (data->ways && data->ways->way->next->content == data->end)
		return (1);
	lstadd(&*queue, lstnew(data->start, 0));
	data->start->visited = uniq_bfs;
	return (0);
}

int			bfs2(t_var *data, int uniq_bfs, t_li *queue, int flag)
{
	t_rst	*tmp;
	t_map	*tmpr;

	if (dop_bfs(data, uniq_bfs, &queue))
		return (0);
	while (queue != NULL && !flag)
	{
		tmpr = pop_queue(&queue);
		tmp = tmpr->link;
		while (tmp && !flag)
		{
			if (tmp->room->visited != uniq_bfs && tmp->room->locked
				!= 1 && tmp->room != data->locked)
			{
				tmp->room->prev = tmpr;
				tmp->room->visited = uniq_bfs;
				lstadd(&queue, lstnew(tmp->room, 0));
				if (tmp->room == data->end)
					flag = 1;
			}
			tmp = tmp->next;
		}
	}
	queuefree(queue);
	return (flag);
}

int			error(char *line, t_var *var, t_map *map)
{
	if (line)
		ft_strdel(&line);
	ft_printf("ERROR\n");
	freelst(var, map);
	return (1);
}

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

int 		dop_push(t_map **tmp2, t_map *tmp, char **mass)
{
	(*tmp2) = (t_map*) malloc(sizeof(t_map));
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
	char 	**mass;
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
		tmp = (t_rst *) malloc(sizeof(t_rst));
		tmp->next = (*cur)->link->next;
		tmp->room = tmp2;
		(*cur)->link->next = tmp;
	}
}

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

int		freem(char **mass)
{
	free(mass[0]);
	free(mass[1]);
	free(mass);
	return (1);
}

int		push_links(t_map *head, t_map *tmp, char **mass)
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

char 		*lines(char *lines, char **line)
{
	char 	*tmp;
	char 	*tmp2;

	tmp2 = ft_new_strjoin(*line, "\n");
	tmp = ft_new_strjoin(lines, tmp2);
	ft_strdel(&tmp2);
	return (tmp);
}



int 		startend(char *line, t_map **map, t_map **dest, char **lins)
{
	if (*dest)
		return (1);
	*lins = lines(*lins, &line);
	while (get_next_line(0, &line) && *line == '#' && ft_strcmp(line,
			"##start") && ft_strcmp(line, "##end") &&
			ft_strcmp(line, "##pin") && ft_strcmp(line, "##lock"))
		*lins = lines(*lins, &line);
	if ((!ft_strchr(line, ' ') || !ft_strchr(ft_strchr(line, ' ') + 1, ' ')
	|| ft_strchr(ft_strchr(ft_strchr(line, ' ') + 1, ' ') + 1, ' ')))
		return (1);
	if (!(*map = push_front(*map, line)))
		return (1);
	*lins = lines(*lins, &line);
	*dest = take_back(*map);
	return (0);
}

int 		dopmain(t_var **var, t_map **map, char **lins)
{
	int     i;
	char 	*line;

	while (get_next_line(0, &line) && line && *line)
	{
		if (!ft_strcmp("##start", line))
		{
			if (startend(line, &*map, &(*var)->start, &(*lins)))
				return (error(line, *var, *map));
		}
		else if (!ft_strcmp("##end", line))
		{
			if (startend(line, &*map, &(*var)->end, &(*lins)))
				return (error(line, *var, *map));
		}
		else if (!ft_strcmp("##pin", line))
		{
			if (startend(line, &*map, &(*var)->pinned, &(*lins)))
				return (error(line, *var, *map));
		}
		else if (!ft_strcmp("##lock", line))
		{
			if (startend(line, &*map, &(*var)->locked, &(*lins)))
				return (error(line, *var, *map));
		}
		else if ((!ft_strchr(line, ' ') || !ft_strchr(ft_strchr(line, ' ') + 1, ' ') || ft_strchr(ft_strchr(ft_strchr(line, ' ') + 1, ' ') + 1, ' ')) && !ft_strchr(line, '-') && *line != '#')
			return (error(line, (*var), *map));
		else if (*line != '#')
		{
			if (ft_strchr(line, '-') && !ft_strchr(ft_strchr(line, '-') + 1, '-') && !ft_strchr(line, ' '))
			{
				if (push_links(*map, *map, ft_strsplit(line, '-')))
					return (error(line, (*var), *map));
				*lins = lines(*lins, &line);
				line = NULL;
			}
			else if (!ft_strchr(line, '-'))
			{
				if (!(*map = push_front(*map, line)))
					return (error(line, (*var), *map));
				*lins = lines(*lins, &line);
				line = NULL;
			}
			else
				return (error(line, (*var), *map));
		}
		else if (!ft_strncmp("#Here is the number of lines required: ", line, 39))
		{
			(*var)->req = ft_atoi(line + 39);
			*lins = lines(*lins, &line);
			line = NULL;
		}
		else
			*lins = lines(*lins, &line);
		line = NULL;
	}
	if (!(*var)->start || !(*var)->end)
		return (error(line, *var, *map));
	i = 1;
	(*var)->ways = NULL;
	while (bfs2((*var), i, 0, 0) && i++)
		store_way(*var, (*var)->end, (*var)->ways, 0);
	if ((*var)->ways)
	{
		ft_printf("%s\n", *lins);
		marafon(*var);
	}
	else
		return (error(line, *var, *map));
	return (0);
}

void		printways(t_var *var)
{
	t_li	*www;
	t_li	*ww;

	www = var->ways;
	if (www)
		ft_printf("\n");
	while (www)
	{
		ww = www->way;
		if (ww)
			ft_printf(BBLUE("[%s]"), ww->content->name);
		ww = ww->next;
		while (ww)
		{
			ft_printf(BBLUE(" -> [%s]"), ww->content->name);
			ww = ww->next;
		}
		www = www->next;
		ft_printf("\n");
	}
}

void		parse_f(char **argv, t_var *var, int argc)
{
	int 	i;

	i = 1;
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "--paths"))
			printways(var);
		if (!ft_strcmp(argv[i], "--lines"))
		{

			ft_printf(BBLUE("\nlines required: %i\n"), var->req);
			if (var->req >= var->lines)
				ft_printf(GREEN("Result: %i\n"), var->lines);
			else
				ft_printf(RED("Result: %i\n"), var->lines);
		}
		else if (!ft_strcmp(argv[i], "--leaks") && ft_printf("\n"))
			system("leaks -q lem-in");
		i++;
	}
}

void		init(t_var **var, t_map **map)
{
	(*var) = malloc(sizeof(t_var));
	(*var)->start = NULL;
	(*var)->end = NULL;
	(*var)->ways = NULL;
	(*var)->pinned = NULL;
	(*var)->locked = NULL;
	(*var)->req = 1;
	(*map) = NULL;
}

int		stat(char *line, char *lins, int argc, char **argv)
{
	t_var	*var;
	t_map	*map;

	lins = ft_strdup("");
	init(&var, &map);
	while (get_next_line(0, &line) && line && *line == '#' &&
		   ft_strcmp(line, "##start") && ft_strcmp(line, "##end"))
		lins = lines(lins, &line);
	if (line && is_digit(line) && ft_atoi(line) > 0)
	{
		var->ants = ft_atoi(line);
		lins = lines(lins, &line);
		if (dopmain(&var, &map, &lins))
		{
			ft_strdel(&lins);
			return (0);
		}
		else if (argc > 1)
			parse_f(argv, var, argc);
	}
	else
	{
		ft_strdel(&lins);
		return (error(line, var, map));
	}
	ft_strdel(&lins);
	freelst(var, map);
}

int			main(int argc, char **argv)
{

	if (argc >= 2 && !ft_strcmp(argv[1], "--help"))
		ft_printf(RED("Usage: ./lem_in [--lines, --paths, --leaks, --help] < map\n"));
	else
		stat(0, ft_strdup(""), argc, argv);
	return (0);
}
