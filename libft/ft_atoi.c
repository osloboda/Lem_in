/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 19:52:43 by osloboda          #+#    #+#             */
/*   Updated: 2018/11/06 15:30:24 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int						ft_atoi(const char *str)
{
	size_t				i;
	unsigned long int	num;
	int					wq;

	num = 0;
	wq = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\v' || str[i] == '\t' ||
			str[i] == '\n' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '-')
		wq = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while ((str[i] != '\0') && ft_isdigit(str[i]))
	{
		if (num >= 9223372036854775807 && wq == 1)
			return (-1);
		else if (num > 9223372036854775807 && wq == -1)
			return (0);
		num = (num * 10) + (str[i++] - '0');
	}
	return ((int)(num * wq));
}
