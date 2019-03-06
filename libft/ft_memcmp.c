/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 17:13:55 by osloboda          #+#    #+#             */
/*   Updated: 2018/10/30 19:32:23 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int						ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*ss1;
	const unsigned char	*ss2;

	i = -1;
	ss1 = (const unsigned char*)s1;
	ss2 = (const unsigned char*)s2;
	while (++i < n)
	{
		if (*(ss1 + i) > *(ss2 + i))
			return (*(ss1 + i) - *(ss2 + i));
		else if (*(ss1 + i) < *(ss2 + i))
			return (*(ss1 + i) - *(ss2 + i));
	}
	return (0);
}
