/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 17:21:53 by osloboda          #+#    #+#             */
/*   Updated: 2018/11/08 13:45:45 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *src)
{
	char	*buffer;
	int		i;

	i = 0;
	while (src[i++])
		;
	if (!(buffer = (char*)malloc(i)))
		return (0);
	while (i--)
		buffer[i] = src[i];
	return (buffer);
}
