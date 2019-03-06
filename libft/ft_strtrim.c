/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 19:17:55 by osloboda          #+#    #+#             */
/*   Updated: 2018/11/02 20:52:18 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	char	*ss;
	int		len;

	if ((char*)s == NULL)
		return (NULL);
	while (*(char*)s == ' ' || *(char*)s == '\n' || *(char*)s == '\t')
		s++;
	len = (int)ft_strlen((char*)s);
	while ((char)s[len - 1] == ' ' || (char)s[len - 1] == '\n' ||
			(char)s[len - 1] == '\t')
		len--;
	if (len <= 0)
		len = 0;
	if (len >= 0)
	{
		if (!(ss = (char*)malloc(1 + len)))
			return (NULL);
	}
	else
		return ((char*)s);
	ft_strncpy(ss, (char*)s, len);
	ss[len] = '\0';
	return (ss);
}
