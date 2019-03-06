/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 18:20:32 by osloboda          #+#    #+#             */
/*   Updated: 2018/10/30 15:22:55 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (s1 != NULL && s2 != NULL)
	{
		while ((*(char*)s1 || *(char*)s2) && n--)
			if (*(char*)s1++ != *(char*)s2++)
				return (0);
		return (1);
	}
	return (0);
}
