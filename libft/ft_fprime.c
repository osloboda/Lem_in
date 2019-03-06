/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprime.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 13:35:11 by osloboda          #+#    #+#             */
/*   Updated: 2018/11/03 17:05:58 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		isprime(int nb)
{
	int			n;

	n = 1;
	while (++n < nb)
		if (nb % n == 0)
			return (0);
	return (1);
}

static int		isprime2(int nb)
{
	int			n;

	n = nb;
	while (--n > 1)
		if (nb % n == 0)
			return (0);
	return (1);
}

void			ft_fprime(int nb)
{
	int			i;

	i = 1;
	if (!isprime2(nb))
	{
		while (++i <= nb)
			if (isprime(i) && nb % i == 0)
			{
				ft_putnbr(i);
				nb /= i;
				if (nb > 2)
					ft_putchar('*');
				i = 2;
			}
		if (i < 2)
			ft_putnbr(1);
	}
	else if (nb > 0)
		ft_putnbr(nb);
	ft_putchar('\n');
}
