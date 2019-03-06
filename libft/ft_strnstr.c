/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 18:49:20 by osloboda          #+#    #+#             */
/*   Updated: 2018/11/02 19:41:31 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	if (*(char*)needle == '\0')
		return ((char*)haystack);
	while (*(char*)haystack != '\0' && len-- >= ft_strlen((char*)needle))
	{
		if ((*haystack == *needle) && (!ft_memcmp((char*)haystack,
						(char*)needle, ft_strlen((char*)needle))))
			return ((char*)haystack);
		haystack++;
	}
	return (NULL);
}
