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
	struct t_rst	*link;
	struct s_map	*next;
}					t_map;

typedef struct		s_var
{
	t_map			*start;
	t_map			*end;
	int 			ants;
}					t_var;

#endif
