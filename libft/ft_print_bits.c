/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 15:03:40 by osloboda          #+#    #+#             */
/*   Updated: 2018/11/03 15:56:55 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_print_bits(unsigned char octet)
{
	int		i;
	int		div;

	i = 8;
	div = 128;
	while (i--)
	{
		if (octet / div == 1)
			ft_putchar('1');
		else
			ft_putchar('0');
		octet = octet % div;
		div /= 2;
	}
}
