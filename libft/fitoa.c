/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fitoa.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 22:34:35 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/04 13:17:54 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int					ftab(unsigned int nb)
{
	unsigned int			n;

	n = 0;
	if (nb < n)
		return (1);
	return (0);
}

char						*freedom(char *a, char *b)
{
	char					*c;

	c = ft_strjoin(a, b);
	free(b);
	return (c);
}

static char					*ass(long int n, char *res, int l)
{
	if (n == (2147483648))
		return (ft_strdup("–2147483648"));
	n *= -1;
	res[0] = '-';
	while (l > 0)
	{
		res[l--] = (char)(n % 10) + 48;
		n /= 10;
	}
	return (res);
}

char						*ft_itoa1(unsigned long long int n)
{
	int						len;
	unsigned long long int	i;
	char					*res;
	unsigned int			nul;

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
	if (ftab(n))
		return (ass(n, res, len));
	else
		while (len >= 0)
		{
			res[len--] = (char)(n % 10) + 48;
			n /= 10;
		}
	return (res);
}
