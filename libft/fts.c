/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 22:35:02 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/04 13:25:53 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long double					llog10(long double n)
{
	return ((n > 1) ? 1 + llog10(n / 10) : 0);
}

char						*ffts3(long double num,
		t_float fts)
{
	fts.i = 0;
	fts.digit = 0;
	while (fts.index != -1 && fts.str[fts.index] != '-')
	{
		fts.wt = pow(10.0, fts.i);
		fts.reminder = fts.whole_part % fts.wt;
		fts.digit = (fts.reminder - fts.digit) / (fts.wt / 10);
		fts.str[fts.index--] = fts.digit + 48;
		fts.i++;
	}
	fts.index = ft_strlen(fts.str) - fts.precision - 1;
	fts.str[fts.index] = '.';
	while (fts.i < fts.precision)
	{
		fts.wt = 10;
		fts.tmp = fts.tmp1 * fts.wt;
		fts.digit = fts.tmp;
		fts.str[++fts.index] = fts.digit + 48;
		fts.tmp1 = fts.tmp - fts.digit;
		fts.i++;
	}
	if (num > -1 && 1.0 / num == 1.0 / -0.0)
		return (freedom("-", fts.str));
	return (fts.str);
}

char						*ffts2(long double num,
		t_float fts)
{
	fts.whole_part = num;
	if (fts.whole_part < 0 && num - fts.whole_part - fts.rst <= -1)
		num = num - fts.rst;
	else if (num - fts.whole_part + fts.rst > 1)
		num = num + fts.rst;
	fts.whole_part = num;
	fts.str = ft_memset(ft_strnew(ft_strlen(ft_itoa(fts.whole_part)) +
			fts.precision + 1), '0', ft_strlen(
			ft_itoa(fts.whole_part)) + fts.precision + 1);
	fts.index = ft_strlen(ft_itoa2(fts.whole_part)) - 1;
	if (fts.whole_part < 0)
	{
		num *= -1;
		fts.whole_part *= -1;
		*fts.str = '-';
	}
	if (num - fts.whole_part + fts.rst >= 1)
		num = num + fts.rst;
	fts.whole_part = num;
	fts.fraction_part = num - fts.whole_part;
	fts.tmp1 = fts.fraction_part + fts.rst;
	return (ffts3(num, fts));
}

char						*ffts(long double num,
		char *script, t_float fts, char *tmp)
{
	tmp = ft_strchr(script, '.');
	if ((fts.precision = 6) && (long)num % 2)
		fts.rst = 0.5;
	else
		fts.rst = 0.49999999999;
	if (tmp && *tmp == '.')
	{
		if (*(tmp + 1) >= '0' && *(tmp + 1) <= '9')
			fts.precision = ft_atoi(tmp + 1);
		else
			fts.precision = 0;
	}
	if (!fts.precision)
	{
		if (num > -1 && num + fts.rst > -1 && num + fts.rst <= 0 && num < 0)
			return (ft_strdup("-0"));
		if (num < 0)
			return (ft_itoa(num - fts.rst));
		return (ft_itoa1(num + fts.rst));
	}
	fts.i = 0;
	while (fts.i++ < fts.precision)
		fts.rst *= 0.1;
	return (ffts2(num, fts));
}

char						*f_t_s(long double num, char *script)
{
	t_float fts;

	fts.rst = 0;
	if (num != num)
	{
		if (script[ft_strlen(script) - 1] == 'F')
			return (ft_strdup("NAN"));
		return (ft_strdup("nan"));
	}
	else if (num == 100.0 / 0.0)
	{
		if (script[ft_strlen(script) - 1] == 'F')
			return (ft_strdup("INF"));
		return (ft_strdup("inf"));
	}
	else if (num == -100.0 / 0.0)
	{
		if (script[ft_strlen(script) - 1] == 'F')
			return (ft_strdup("-INF"));
		return (ft_strdup("-inf"));
	}
	return (ffts(num, script, fts, ""));
}
