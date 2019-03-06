/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taketype.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 22:35:47 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/04 13:19:09 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char						*check_per(char *str)
{
	int						i;
	char					*script;

	i = 0;
	script = NULL;
	while (str[i] != 'd' && str[i] != 'D' && str[i] != 'i' && str[i] != 'o' &&
			str[i] != 'O' && str[i] != 'c' && str[i] != 's' && str[i] != 'p' &&
			str[i] != 'u' && str[i] != 'x' && str[i] != 'F' && str[i] != 'X' &&
			str[i] != 'f' && str[i] != '%' && str[i] != 'U' && (str[i] == 'h' ||
			str[i] == 'l' || str[i] == '#' || str[i] == '.' || (str[i] >=
			'0' && str[i] <= '9') || str[i] == ' ' || str[i] == 'j' ||
			str[i] == 'z' || str[i] == 't' || str[i] == 'L' || str[i] == '-'
			|| str[i] == '+'))
		i++;
	if (str[i] != 'd' && str[i] != 'D' && str[i] != 'i' && str[i] != 'o' &&
			str[i] != 'O' && str[i] != 'c' && str[i] != 's' && str[i] != 'p' &&
			str[i] != 'u' && str[i] != 'x' && str[i] != 'X' && str[i] != 'f' &&
			str[i] != '%' && str[i] != 'U' && str[i] != 'F')
		i--;
	if (i != (int)ft_strlen(str))
		script = ft_strsub(str, 0, (size_t)i + 1);
	return (script);
}

double						pow(double a, double b)
{
	double					s;
	double					i;

	i = 0;
	s = a;
	while (i < b)
	{
		s = s * a;
		i++;
	}
	return (s);
}

unsigned long long int		taketype(char *script, int ssize,
		va_list tr, unsigned long long int ret)
{
	if (script[ssize - 1] == 'l' && script[ssize - 2] == 'l')
		ret = va_arg(tr, unsigned long long int);
	else if (script[ssize - 1] == 'l')
		ret = va_arg(tr, unsigned long int);
	else if (script[ssize - 2] == 'l' && script[ssize - 3] == 'l'
			&& script[ssize - 1] == '#')
		ret = va_arg(tr, unsigned long long int);
	else if (script[ssize - 2] == 'l' && script[ssize - 1] == '#')
		ret = va_arg(tr, unsigned long int);
	else if (script[ssize - 1] == 'j')
		ret = va_arg(tr, uintmax_t);
	else if (script[ssize - 1] == 'z')
		ret = va_arg(tr, size_t);
	else if (script[ssize] == 'O' || script[ssize]
			== 'U' || script[ssize - 1] == 't')
		ret = va_arg(tr, unsigned long int);
	else
		ret = va_arg(tr, unsigned int);
	return (ret);
}

char						*uox(va_list tr, char *script, int ssize)
{
	unsigned long long int	ret;

	if (script[ssize - 1] == 'h' && script[ssize] !=
			'O' && script[ssize] != 'U')
	{
		if (script[ssize - 2] == 'h')
			ret = (unsigned char)va_arg(tr, unsigned int);
		else
			ret = (unsigned short int)va_arg(tr, unsigned int);
	}
	else
		ret = taketype(script, ssize, tr, 0);
	if (script[ssize] == 'o')
		return (ft_itoa_base(ret, 8, 0, 0));
	else if (script[ssize] == 'O')
		return (ft_itoa_base(ret, 8, 1, 0));
	else if (script[ssize] == 'x')
		return (ft_itoa_base(ret, 16, 0, 0));
	else if (script[ssize] == 'X')
		return (ft_itoa_base(ret, 16, 1, 0));
	else if (script[ssize] == 'u' || script[ssize] == 'U')
		return (ft_itoa1(ret));
	return (NULL);
}

char						*di(va_list tr, char *script,
		long long int ret, int ssize)
{
	char					*res;

	if (script[ssize - 2] == 'l' || script[ssize - 1] == 'D')
	{
		if (script[ssize - 3] == 'l')
			ret = va_arg(tr, long long int);
		else
			ret = va_arg(tr, long int);
	}
	else if (script[ssize - 2] == 'h' && script[ssize - 3] == 'h')
		ret = (signed char)va_arg(tr, int);
	else if (script[ssize - 2] == 'h' && script[ssize - 3] == 'z')
		ret = va_arg(tr, size_t);
	else if (script[ssize - 2] == 'h' && script[ssize - 3] == 'j')
		ret = va_arg(tr, uintmax_t);
	else if (script[ssize - 2] == 'h')
		ret = (short int)va_arg(tr, int);
	else if (script[ssize - 2] == 'j')
		ret = va_arg(tr, uintmax_t);
	else if (script[ssize - 2] == 'z' || script[ssize - 2] == 't')
		ret = va_arg(tr, size_t);
	else
		ret = va_arg(tr, int);
	res = ft_itoa2(ret);
	return (res);
}
