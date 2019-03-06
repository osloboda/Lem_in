/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createfield.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 22:33:53 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/04 13:20:30 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int							*dop_get(char *arg, int *flags,
		char *script, int ssize)
{
	if (!flags[2] && *script == ' ' && *arg != '+' && *(script + 1)
			!= '+' && *(script + 2) != '+' && *arg != '-' && (script[ssize - 1]
			== 'd' || script[ssize - 1] == 'D' || script[ssize - 1] == 'i' ||
			script[ssize - 1] == 'f' || script[ssize - 1] == 'F'))
		flags[4] = 1;
	if (ft_strcmp(arg, "inf") == 0 || ft_strcmp(arg, "-inf") == 0
			|| ft_strcmp(arg, "-INF") == 0 || ft_strcmp(arg, "INF") == 0)
		return (flags);
	if (*script == '0' && !flags[2] && *(script + 1) != '-'
			&& *(script + 2) != '+' && *(script + 2) != '-')
		flags[3] = '0';
	if (*arg == '-' && flags[3] == '0' && !flags[2])
		flags[5] = 1;
	return (flags);
}

int							*get_flags(char **arg, int *flags,
		char *script, int ssize)
{
	if (*script == '-' && !(flags[5] = 0))
		flags[2] = 1;
	if (ft_strcmp(*arg, "NAN") == 0 || ft_strcmp(*arg, "nan") == 0)
		return (flags);
	if (*script == '+' && *(script + 1) != '0' && **arg != '+' &&
			flags[3] != '0' && **arg != '-' && (script[ssize - 1] == 'd' ||
			script[ssize - 1] == 'D' || script[ssize - 1] == 'i' ||
			script[ssize - 1] == 'f' || script[ssize - 1] == 'F'))
		*arg = freedom("+", *arg);
	else if (*script == '+' && **arg != '-' && **arg != '+' &&
			(script[ssize - 1] == 'd' || script[ssize - 1] == 'D' ||
					script[ssize - 1] == 'i' || script[ssize - 1] == 'f' ||
					script[ssize - 1] == 'F'))
		flags[0] = 1;
	return (dop_get(*arg, flags, script, ssize));
}

int							check_null(char *arg)
{
	while (*arg)
	{
		if (*arg != '0')
			return (1);
		arg++;
	}
	return (0);
}

char						*cre1(char *script,
		char *arg, int ssize, int *flags)
{
	char					*tmp;

	if (ft_strcmp(arg, "NAN") != 0 && ft_strcmp(arg, "nan") != 0
			&& ft_strcmp(arg, "inf") != 0 && ft_strcmp(arg, "-inf") != 0
			&& ft_strcmp(arg, "-INF") != 0 && ft_strcmp(arg, "INF") != 0)
	{
		if (!(ft_strchr(script, '-') && ft_strchr(script, '#') &&
				ft_strchr(script, '0') && ft_strchr(script, '+') &&
				ft_strchr(script, '.') && ft_strchr(script, ' ') &&
				ssize >= 24 && script[ssize - 1] == 'd'))
		{
			tmp = dot(arg, script, &flags[6], ssize);
			arg = tmp;
		}
		if ((script[ssize - 1] == 'f' || script[ssize - 1] == 'F')
				&& ft_strchr(script, '#') && flags[6] <= 0)
		{
			tmp = ft_strjoin(arg, ".");
			free(arg);
			arg = tmp;
		}
	}
	return (arg);
}

int							*check_flags(char **script,
		int *flags, char **arg, int *ssize)
{
	if (**script == '#' && (**arg != '0' && ((*script)[*ssize - 1]
			== 'o' || (*script)[*ssize - 1] == 'O')))
		flags[7] = 1;
	if (**script == '#' && (check_null(*arg) && ((*script)[*ssize - 1]
			== 'x' || (*script)[*ssize - 1] == 'X')))
		flags[7] = 1;
	if ((*script)[*ssize - 1] == 'p')
		flags[7] = 1;
	flags = get_flags(&(*arg), flags, *script, *ssize);
	if (**script == '.')
	{
		(*script)++;
		(*ssize)--;
		while (**script >= '0' && **script <= '9' && (*ssize)--)
			(*script)++;
	}
	return (flags);
}
