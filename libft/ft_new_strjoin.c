/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_strjoin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 13:22:19 by osloboda          #+#    #+#             */
/*   Updated: 2019/02/24 13:25:07 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_new_strjoin(char *str1, char const *str2)
{
	char *new;
	char *pointer;
	char *temp;

	temp = NULL;
	if (!(new = (char *)malloc(ft_strlen(str1) + ft_strlen(str2) + 1)))
		return (0);
	if (new)
	{
		temp = new;
		if (str1)
		{
			pointer = str1;
			while (*str1)
				*(new++) = *(str1++);
			ft_strdel(&pointer);
		}
		if (str2)
			while (*str2)
				*(new++) = *(str2++);
		*new = '\0';
	}
	return (temp);
}
