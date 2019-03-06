/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_bits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 16:41:45 by osloboda          #+#    #+#             */
/*   Updated: 2018/11/06 15:37:27 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned char		ft_reverse_bits(unsigned char octet)
{
	int				i;
	unsigned char	octet2;

	i = 8;
	octet2 = octet;
	octet >>= 1;
	while (--i)
	{
		octet2 <<= 1;
		octet2 |= octet & 1;
		octet >>= 1;
	}
	octet2 <<= i;
	return (octet2);
}
