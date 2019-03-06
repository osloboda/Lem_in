/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 21:43:23 by osloboda          #+#    #+#             */
/*   Updated: 2018/11/04 18:26:06 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			find(char *str, char c)
{
	int		q;
	int		g;

	q = 0;
	g = 0;
	while (*str != '\0')
	{
		while (*str != '\0' && *str == c)
			str++;
		while (*str != '\0' && *str != c)
		{
			str++;
			g++;
		}
		if (g)
		{
			q++;
			g = 0;
		}
	}
	return (q + 1);
}

static int	count(int n, char *str, char c)
{
	while (str[++n] != '\0' && str[n] != c)
		;
	return (n);
}

static void	init_vars(int *i, int *g)
{
	*i = 0;
	*g = -1;
}

int			count2(char *str, char c, int i)
{
	while (str[i] != '\0' && str[i] == c)
		i++;
	return (i);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		g;
	int		b;
	char	**buff;
	int		n;

	if (s == NULL || !(buff = (char**)malloc(find((char*)s,
						c) * sizeof(char*))))
		return (NULL);
	init_vars(&i, &g);
	while (s[i])
	{
		b = 0;
		i = count2((char*)s, c, i);
		n = i - 1;
		if (s[i] != c && s[i] != '\0')
			buff[++g] = (char*)malloc(count(n, (char*)s,
						c) - i + 1 * sizeof(char));
		while (s[i] != c && s[i] != '\0')
			buff[g][b++] = s[i++];
		if (s[i])
			buff[g][b] = '\0';
	}
	buff[++g] = NULL;
	return (buff);
}
