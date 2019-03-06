/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 17:09:30 by osloboda          #+#    #+#             */
/*   Updated: 2018/11/06 14:55:47 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnew(size_t size)
{
	char	*s;

	if (size < 1)
		return (ft_strdup("\0"));
	if (!(s = (char*)malloc(size + 1)))
		return (NULL);
	ft_memset(s, '\0', size + 1);
	return (s);
}
