/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 18:27:52 by osloboda          #+#    #+#             */
/*   Updated: 2018/10/29 19:03:12 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ss;

	if (s == NULL)
		return (NULL);
	if (!(ss = malloc(len + 1)))
		return (NULL);
	ft_strncpy(ss, &s[start], len);
	*(ss + len) = '\0';
	return (ss);
}
