/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powitoab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 22:35:22 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/04 13:18:29 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long int		ft_pow(unsigned long long int nb, int pow)
{
	if (pow == 0)
		return (1);
	else
		return (nb * ft_pow(nb, pow - 1));
}

static int					ftab1(long long int nb)
{
	int						n;

	n = 0;
	if (nb < n)
		return (1);
	return (0);
}

static char					*ass1(unsigned long long int n, char *res, int l)
{
	n *= -1;
	res[0] = '-';
	while (l > 0)
	{
		res[l--] = (unsigned char)(n % 10) + 48;
		n /= 10;
	}
	return (res);
}

char						*ft_itoa2(long long int n)
{
	int						len;
	long long int			i;
	char					*res;
	int						nul;

	len = 1;
	i = n;
	nul = 0;
	while (i /= 10)
		len++;
	if (n < nul)
		len++;
	if (!(res = (char *)malloc(len + 1)))
		return (NULL);
	res[len--] = '\0';
	if (ftab1(n))
		return (ass1(n, res, len));
	else
		while (len >= 0)
		{
			res[len--] = (char)(n % 10) + 48;
			n /= 10;
		}
	return (res);
}

char						*ft_itoa_base(unsigned long long int va,
		unsigned int base, int uppercase, unsigned long long int n)
{
	int						in[2];
	char					*nbr;

	in[0] = 1;
	in[1] = 0;
	if (va < n)
	{
		if (base == 10)
			in[1] = 1;
		va *= -1;
	}
	while (ft_pow(base, in[0]) - 1 < va)
		in[0]++;
	nbr = ft_strnew(in[0]);
	while (in[0]-- > 0)
	{
		if (uppercase)
			nbr[in[0] + in[1]] = (va % base) + (va % base > 9 ? 'A' - 10 : '0');
		else
			nbr[in[0] + in[1]] = (va % base) + (va % base > 9 ? 'a' - 10 : '0');
		va = va / base;
	}
	if (in[1])
		nbr[0] = '-';
	return (nbr);
}
