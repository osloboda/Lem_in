/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:46:23 by osloboda          #+#    #+#             */
/*   Updated: 2018/10/30 19:32:39 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memcpy(void *destptr,
		const void *srcptr, size_t num)
{
	const char	*s;
	char		*d;

	d = destptr;
	s = srcptr;
	while (num--)
		*d++ = *s++;
	return (destptr);
}
