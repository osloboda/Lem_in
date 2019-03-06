/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 19:03:54 by osloboda          #+#    #+#             */
/*   Updated: 2018/11/06 17:27:15 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(s = (char*)malloc(1 + ft_strlen((char*)s1) + ft_strlen((char*)s2))))
		return (NULL);
	s = ft_strcpy(s, (char*)s1);
	s = ft_strcat(s, (char*)s2);
	s[ft_strlen(s) + 1] = '\0';
	return (s);
}
