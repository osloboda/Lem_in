/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 18:13:02 by osloboda          #+#    #+#             */
/*   Updated: 2018/10/29 18:15:21 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ss;
	unsigned int	i;

	i = 0;
	if ((char*)s == NULL)
		return (NULL);
	if (!(ss = (char*)malloc(1 + ft_strlen((char*)s))))
		return (NULL);
	while (i < (unsigned int)ft_strlen((char*)s))
	{
		ss[i] = f(i, (char)s[i]);
		i++;
	}
	ss[i] = '\0';
	return (ss);
}
