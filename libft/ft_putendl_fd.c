/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 19:44:38 by osloboda          #+#    #+#             */
/*   Updated: 2018/10/30 19:54:56 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_putendl_fd(char const *s, int fd)
{
	char	*p;

	if (s != NULL)
	{
		p = (char*)s;
		while (*p)
		{
			ft_putchar_fd(*p, fd);
			p++;
		}
		ft_putchar_fd('\n', fd);
	}
}
