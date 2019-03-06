/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 22:35:34 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/04 13:21:05 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char						*dot_set(char *script,
		char *arg, int *i, int *precision)
{
	char					*tmp;
	char					*tmp1;
	char					*fild;
	int						flag;

	tmp1 = arg;
	flag = 0;
	if (*arg == '-' && arg++)
		flag++;
	fild = (char *)malloc(ft_atoi(script + *i) -
			ft_strlen(arg) + 1 * sizeof(char));
	fild[ft_atoi(script + *i) - ft_strlen(arg)] = '\0';
	tmp = ft_strjoin(ft_memset(fild, '0', ft_atoi(script + *i) -
			ft_strlen(arg)), arg);
	free(fild);
	free(tmp1);
	arg = tmp;
	if (flag == 1)
		arg = freedom("-", arg);
	if (script[ft_strlen(script) - 1] != 'c')
		*precision = ft_atoi(script + *i);
	return (arg);
}

char						*cap_set(char *scr,
		char *arg, int *i, int *precision)
{
	char					*tmp;

	if (scr[ft_strlen(scr) - 1] != 's' &&
			scr[ft_strlen(scr) - 1] != 'f' &&
			scr[ft_strlen(scr) - 1] != 'F' &&
			scr[ft_strlen(scr) - 1] != '%')
	{
		if ((int)(ft_atoi(scr + ++*i) - ft_strlen(arg)) >= 0 &&
				scr[ft_strlen(scr) - 1] != 'c')
			arg = dot_set(scr, arg, &(*i), &(*precision));
		else if (*arg == '0' || (*arg == ' ' && *(arg + 1) == '0'))
		{
			free(arg);
			arg = ft_strdup("");
		}
		if (scr[ft_strlen(scr) - 1] != 'c')
			*precision = ft_atoi(scr + *i);
	}
	else if (scr[ft_strlen(scr) - 1] != 'f' && scr[ft_strlen(scr) - 1] != 'F')
	{
		tmp = ft_strsub(arg, 0, (size_t)ft_atoi(scr + ++*i));
		free(arg);
		arg = tmp;
	}
	return (arg);
}

char						*change_pr(char *script,
		int ssize, char *arg, int *precision)
{
	char					*tmp;
	int						i;

	if (!ft_strchr(script, '.') && *precision == -1 &&
			(script[ssize - 1] == 'f' || script[ssize - 1] == 'F'))
		*precision = 6;
	else if ((script[ssize - 1] == 'f' || script[ssize - 1] == 'F')
			&& ft_strchr(script, '.'))
		*precision = ft_atoi(ft_strchr(script, '.') + 1);
	i = 0;
	while (script[i])
	{
		if (script[i] == '%')
		{
			tmp = ft_strjoin(arg, "%");
			free(arg);
			arg = tmp;
			break ;
		}
		i++;
	}
	return (arg);
}

char						*dot(char *arg, char *script,
		int *precision, int ssize)
{
	int						i;

	i = 0;
	arg = freedom("", arg);
	while (script[i])
	{
		if (script[i] == '.' && script[i + 1] >= '0' && script[i + 1] <= '9')
		{
			arg = cap_set(script, arg, &i, &(*precision));
			break ;
		}
		if (script[i] == '.' && !ft_isdigit(script[i + 1]) && (*arg == '0'
				|| script[ssize - 1] == 's') && script[ssize - 1] != 'f' &&
				script[ssize - 1] != 'F')
		{
			free(arg);
			arg = ft_strdup("");
			*precision = 0;
		}
		i++;
	}
	return (change_pr(script, ssize, arg, &(*precision)));
}
