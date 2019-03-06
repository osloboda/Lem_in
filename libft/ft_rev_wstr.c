/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_wstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 14:03:03 by osloboda          #+#    #+#             */
/*   Updated: 2018/11/06 15:05:55 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_print(char *s, int a)
{
	char		c;

	while (s[a] != ' ' && s[a] != '\0')
	{
		c = s[a];
		ft_putchar(c);
		a++;
	}
}

void			ft_rev_wstr(char *str)
{
	int			len;

	if (str == NULL)
		return ;
	len = ft_strlen(str - 1);
	while (len > 0)
	{
		while (str[len] != ' ' && len != 0)
			len--;
		ft_print(str, len + 1);
		if (str[len] == ' ')
			ft_putchar('\n');
		len--;
	}
}
