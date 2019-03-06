/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 15:44:47 by osloboda          #+#    #+#             */
/*   Updated: 2018/11/02 16:38:22 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ftab(int nb)
{
	if (nb < 0)
		return (1);
	return (0);
}

static char	*ass(long int n, char *res, int l)
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

char		*ft_itoa(int n)
{
	int		len;
	int		i;
	char	*res;

	len = 1;
	i = n;
	while (i /= 10)
		len++;
	if (n < 0)
		len++;
	if (!(res = (char*)malloc(len + 1)))
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
