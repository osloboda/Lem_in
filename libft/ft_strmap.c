/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 17:51:38 by osloboda          #+#    #+#             */
/*   Updated: 2018/11/02 19:40:57 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	char	*ss;
	int		i;

	i = 0;
	if ((char*)s == NULL)
		return (NULL);
	if (!(ss = (char*)malloc(1 + ft_strlen((char*)s))))
		return (NULL);
	while (i < (int)ft_strlen((char*)s))
	{
		ss[i] = f((char)s[i]);
		i++;
	}
	ss[i] = '\0';
	return (ss);
}
