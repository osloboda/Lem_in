/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:38:13 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/04 13:17:19 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int							*firsthash(char *script,
		int *flags, char **arg, int ssize)
{
	if (ft_strchr(script, '+') && **arg != '-' && **arg != '+' &&
			(script[ssize - 1] == 'd' || script[ssize - 1] == 'D' ||
					script[ssize - 1] == 'i' || script[ssize - 1] == 'f' ||
					script[ssize - 1] == 'F'))
		flags = get_flags(&(*arg), flags, ft_strchr(script, '+'),
				ft_strlen(ft_strchr(script, '+')));
	if (flags[7] && (flags[3] == ' ' || (**arg != '0' &&
			(ft_atoi(script) <= (int)ft_strlen(*arg) + 3) &&
			script[ssize - 1] != 'p')))
	{
		if (**arg && (script[ssize - 1] == 'x' ||
				script[ssize - 1] == 'p'))
			*arg = freedom("0x", *arg);
		else if (*arg && script[ssize - 1] == 'X')
			*arg = freedom("0X", *arg);
		else if (**arg != '0')
			*arg = freedom("0", *arg);
		flags[3] = ' ';
	}
	return (flags);
}

char						*sechash(char *script,
		int *flags, char *arg, int ssize)
{
	if (flags[7] && flags[3] == '0')
	{
		if ((script[ssize - 1] == 'x' ||
				script[ssize - 1] == 'p') && *arg)
			arg = freedom("0x", arg);
		else if (*arg && script[ssize - 1] == 'X')
			arg = freedom("0X", arg);
		else if (*arg != '0')
			arg = freedom("0", arg);
	}
	if (flags[0] && *arg)
		arg = freedom("+", arg);
	if (flags[4] && *arg)
		arg = freedom(" ", arg);
	free(flags);
	return (arg);
}

char						*trirdhash(char *script,
		int *flags, char *arg, int ssize)
{
	if (flags[7])
	{
		if ((*arg && *arg != '0' && script[ssize - 1] == 'x') ||
				script[ssize - 1] == 'p')
			arg = freedom("0x", arg);
		else if (*arg && script[ssize - 1] == 'X')
			arg = freedom("0X", arg);
		else if ((*(script - 1) == 'o' || *(script - 1) == 'O') && *arg != '0')
			arg = freedom("0", arg);
	}
	if (*(script - 1) != 's' && *(script - 1) != 'U' && *(script - 1) != 'O')
	{
		if (flags[0])
			arg = freedom("+", arg);
		if (flags[4])
			arg = freedom(" ", arg);
	}
	free(flags);
	return (arg);
}

char						*create_field(char *script, char *arg, int ssize)
{
	int						*flags;
	char					*tmp;
	int						i;

	flags = (int *)malloc(8 * sizeof(int));
	i = -1;
	while (i++ < 7)
		flags[i] = 0;
	flags[3] = 32;
	flags[6] = -1;
	arg = cre1(script, arg, ssize, flags);
	while (*script)
	{
		flags = check_flags(&script, flags, &arg, &ssize);
		if (*script >= '1' && *script <= '9')
		{
			flags = firsthash(script, flags, &arg, ssize);
			tmp = fill(script, arg, flags, ssize);
			arg = tmp;
			return (sechash(script, flags, arg, ssize));
		}
		script++;
		ssize--;
	}
	return (trirdhash(script, flags, arg, ssize));
}

char						*cstr(char *arg, char *script, int ssize)
{
	if (arg == NULL)
		return (create_field(script, ft_strdup("(null)"), ssize));
	else if (script[ssize - 1] == 's')
		return (create_field(script, ft_strdup(arg), ssize));
	return (create_field(script, arg, ssize));
}
