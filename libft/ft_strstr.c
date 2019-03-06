/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 18:39:59 by osloboda          #+#    #+#             */
/*   Updated: 2018/10/28 14:21:36 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strstr(const char *haystack, const char *needle)
{
	const char	*h;
	const char	*n;

	if (*(char*)haystack == '\0' && *(char*)needle == '\0')
		return ((char*)haystack);
	while (*haystack)
	{
		h = haystack;
		n = needle;
		while (*h == *n && *h && *n)
		{
			h++;
			n++;
		}
		if (*(char*)n == '\0')
			return ((char*)haystack);
		haystack++;
	}
	return (NULL);
}
