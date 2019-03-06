/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 16:21:16 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/04 13:19:26 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char						*dooper(char *script, int ssize, va_list tr)
{
	if (script[ssize - 1] == 'p')
		return (cstr(ft_itoa_base(va_arg(tr, unsigned long long),
				16, 0, 0), script, ssize));
	else if (script[ssize - 1] == 's')
		return (cstr(va_arg(tr, char*), script, ssize));
	else if (script[ssize - 1] == '%')
		return (cstr(ft_strdup(""), script, ssize));
	else if (script[ssize - 1] == 'f' || script[ssize - 1] == 'F')
	{
		if (script[ssize - 2] != 'L')
			return (cstr(f_t_s(va_arg(tr, double), script), script, ssize));
		return (cstr(f_t_s(va_arg(tr, long double), script), script, ssize));
	}
	else if (script[ssize - 1] == 'o' || script[ssize - 1] == 'O' ||
			script[ssize - 1] == 'x' || script[ssize - 1] == 'X' ||
			script[ssize - 1] == 'u' || script[ssize - 1] == 'U')
		return (cstr(uox(tr, script, ssize - 1), script, ssize));
	else if (script[ssize - 1] == 'i' || script[ssize - 1] == 'd'
			|| script[ssize - 1] == 'D')
		return (cstr(di(tr, script, 0, ssize), script, ssize));
	return (ft_strdup(""));
}

char						*operate(char *script,
		va_list tr, int *bites, int ssize)
{
	char					*ret;
	char					*outt;

	if (script[ssize - 1] == 'c')
	{
		ret = (char *)malloc(2 * sizeof(char));
		ret[1] = '\0';
		if (script[ssize - 2] == 'l')
			ret[0] = (wchar_t)va_arg(tr, unsigned int);
		else
			ret[0] = (char)va_arg(tr, int);
		if (ret[0] == 0)
		{
			outt = cstr(ret, script, ssize);
			if (*outt)
				outt[ft_strlen(outt) - 1] = '\0';
			*bites += write(1, outt, ft_strlen(outt) + 1);
			free(outt);
			return (ft_strdup(""));
		}
		return (cstr(ret, script, ssize));
	}
	else
		return (dooper(script, ssize, tr));
}

void						dop_takes(char *outt, int **bites,
		char *script, const char **format)
{
	*format += ft_strlen(script);
	**bites += write(1, outt, ft_strlen(outt));
	free(outt);
	free(script);
	script = NULL;
}

void						take_script(const char *format, va_list tr,
		int *bites, char *outt)
{
	char					*script;

	while (*format)
	{
		if (ft_strchr(format, '%'))
		{
			if (ft_strchr(format, '%') - format > 0 && (outt =
					ft_strsub(format, 0, ft_strchr(format, '%') - format)))
			{
				*bites += write(1, outt, ft_strlen(outt));
				free(outt);
			}
			format = 1 + ft_strchr(format, '%');
			script = check_per((char *)format);
			if (script && (outt = operate(script,
					tr, &*bites, (int)ft_strlen(script))))
				dop_takes(outt, &bites, script, &format);
			continue;
		}
		outt = (char *)format;
		*bites += (size_t)write(1, outt, ft_strlen(outt));
		format += ft_strlen(format);
	}
}

int							ft_printf(const char *fmt, ...)
{
	va_list					tr;
	int						bites;

	bites = 0;
	va_start(tr, fmt);
	take_script(fmt, tr, &bites, "");
	va_end(tr);
	return (bites);
}
