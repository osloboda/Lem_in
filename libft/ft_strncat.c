/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 18:17:55 by osloboda          #+#    #+#             */
/*   Updated: 2018/10/27 18:06:17 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncat(char *restrict s1, const char *restrict s2, size_t n)
{
	int		i;
	int		j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (s1[i] != '\0')
		i++;
	while (s2[j] != '\0' && k < n)
	{
		s1[i + j] = s2[j];
		j++;
		k++;
	}
	s1[i + j] = '\0';
	return (s1);
}
