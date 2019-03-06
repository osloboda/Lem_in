/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 19:31:38 by osloboda          #+#    #+#             */
/*   Updated: 2018/10/28 14:58:22 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = -1;
	while ((*s1 || *s2) && (++i < n))
	{
		if (*s1 != *s2)
			return (*(const unsigned char*)s1 - *(const unsigned char*)s2);
		s1++;
		s2++;
	}
	return (0);
}
