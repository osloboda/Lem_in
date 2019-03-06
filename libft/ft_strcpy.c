/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 17:24:06 by osloboda          #+#    #+#             */
/*   Updated: 2018/10/27 12:57:28 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpy(char *destptr, const char *srcptr)
{
	int	i;

	i = 0;
	while (srcptr[i] != '\0')
	{
		destptr[i] = srcptr[i];
		i++;
	}
	destptr[i] = '\0';
	return (destptr);
}
