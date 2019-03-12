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

# ifndef LEM_IN_H
#define LEM_IN_H

#include "../libft/libft.h"
#include "limits.h"

typedef struct		s_map	t_map;

typedef struct		s_rst
{
	t_map			*room;
	struct s_rst	*next;
}					t_rst;

typedef struct		s_map
{
	char			*name;
	int 			x;
	int 			y;
	int             visited;
	int             locked;
	int 			ant;
	struct s_rst	*link;
	struct s_map	*next;
    struct s_map	*prev;
}					t_map;

typedef struct		s_li
{
	struct s_map	*content;
	size_t			content_size;
	struct s_li 	*way;
	int 			way_lenght;
	struct s_li 	*next;
	struct s_li 	*prev;
}					t_li;

typedef struct		s_var
{
	t_map			*start;
	t_map			*end;
	t_map			*pinned;
	t_map			*locked;
	t_li			*ways;
	int 			lines;
	int 			ants;
	int 			req;
}					t_var;

#endif
