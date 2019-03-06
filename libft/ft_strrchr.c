/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 18:36:41 by osloboda          #+#    #+#             */
/*   Updated: 2018/11/02 20:08:04 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	char	*ss;

	ss = 0;
	if (c == 0)
		ss = (char*)&s[(int)ft_strlen((char*)s)];
	while (*s)
	{
		if (*s == c)
			ss = (char*)s;
		s++;
	}
	return (ss);
}
