/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 13:03:35 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/04 13:04:35 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"
# include "limits.h"

# define REQ "#Here is the number of lines required: "

typedef struct		s_rst
{
	struct s_map	*room;
	struct s_rst	*next;
}					t_rst;

typedef struct		s_map
{
	char			*name;
	int				x;
	int				y;
	int				visited;
	int				locked;
	int				ant;
	struct s_rst	*link;
	struct s_map	*next;
	struct s_map	*prev;
}					t_map;

typedef struct		s_li
{
	struct s_map	*content;
	size_t			content_size;
	struct s_li		*way;
	int				way_lenght;
	struct s_li		*next;
	struct s_li		*prev;
}					t_li;

typedef struct		s_bist
{
	char			*content;
	size_t			content_size;
	struct s_bist	*next;
	struct s_bist	*prev;
}					t_bist;

typedef struct		s_var
{
	t_map			*start;
	t_map			*end;
	t_map			*pinned;
	t_map			*locked;
	t_li			*ways;
	int				lines;
	int				ants;
	int				req;
}					t_var;

int					dopmain(t_var **var, t_map **map, t_bist **lins);
int					is_digit(char *line);
void				lines(t_bist *lines, int flag);
int					bfs2(t_var *data, int uniq_bfs, t_li *queue, int flag);
int					error(char *line, t_var *var, t_map *map, t_bist *lins);
void				freelst(t_var *var, t_map *map);
void				lstadd(t_li **alst, t_li *new);
t_li				*lstnew(t_map *content, size_t content_size);
int					startend(char **line, t_map **map,
		t_map **dest, t_bist **lins);
t_map				*push_front(t_map *head, char *line);
void				store_way(t_var *var, t_map *going, t_li *w, int i);
int					push_links(t_map *head, t_map *tmp, char **mass);
void				dop_dest(t_rst *tmp, t_map *tmp2, t_map **cur);
void				marafon(t_var *var);
void				ftlstadd(t_bist **alst, t_bist *new);
t_bist				*ftlstnew(char *content, size_t content_size);
void				free_mass(char **mass);
int					freem(char **mass);

#endif
