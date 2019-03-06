/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 17:44:52 by osloboda          #+#    #+#             */
/*   Updated: 2018/11/02 20:26:22 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncpy(char *dst, const char *src, size_t n)
{
	char	*d;
	size_t	i;

	i = -1;
	d = dst;
	while (++i < n && src[i] != '\0')
		d[i] = src[i];
	i--;
	while (++i < n)
		d[i] = '\0';
	return (dst);
}
