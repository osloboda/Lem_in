/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 22:34:17 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/04 13:17:39 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int							*f_flags(char *script, int *flags, int ssize)
{
	flags[1] = ft_atoi(script);
	if (flags[7] && flags[3] == '0')
		flags[1] -= 2;
	if (flags[6] >= 0 && flags[6] < flags[1] && !flags[5] &&
			script[ssize - 1] != 'f' && script[ssize - 1] != 'F' &&
			script[ssize - 1] != 's')
		flags[3] = ' ';
	if (flags[4])
		flags[1]--;
	if (flags[0])
		flags[1]--;
	return (flags);
}

char						*set_sign(int *flags,
		char *arg, char *field, char *tmp1)
{
	char					*tmp;

	if (flags[0] && flags[3] == ' ' && !(flags[0] = 0))
	{
		tmp = ft_strjoin("+", arg);
		free(tmp1);
		tmp1 = tmp;
		arg = tmp;
	}
	if (flags[2])
	{
		tmp = ft_strjoin(arg, field);
		free(field);
		free(tmp1);
		arg = tmp;
	}
	else
	{
		tmp = ft_strjoin(field, arg);
		free(field);
		free(tmp1);
		arg = tmp;
	}
	return (arg);
}

char						*dop_fil_arg(int *flags, char *arg, char *tmp1)
{
	char					*field;
	char					*spaces;

	spaces = (char *)malloc(sizeof(char) * (flags[1] - ft_strlen(arg) + 1));
	spaces[(flags[1] - ft_strlen(arg))] = '\0';
	field = ft_memset(spaces, flags[3], (flags[1] - ft_strlen(arg)));
	if (*arg == '-' && flags[3] == '0' && (flags[5]))
		arg++;
	return (set_sign(flags, arg, field, tmp1));
}

char						*fill(char *script, char *arg,
		int *flags, int ssize)
{
	char					*tmp1;

	tmp1 = arg;
	flags = f_flags(script, flags, ssize);
	if (!flags[1])
	{
		tmp1 = ft_strdup(arg);
		free(arg);
		return (tmp1);
	}
	else if (flags[1] < (int)ft_strlen(arg))
	{
		tmp1 = ft_strdup(arg);
		free(arg);
		return (tmp1);
	}
	arg = dop_fil_arg(flags, arg, tmp1);
	if (flags[0] && flags[3] != ' ' && !(flags[0] = 0))
		arg = freedom("+", arg);
	if (flags[4] && !(flags[4] = 0))
		arg = freedom(" ", arg);
	if (flags[5] && !(flags[5] = 0))
		arg = freedom("-", arg);
	return (arg);
}
