/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 14:49:18 by osloboda          #+#    #+#             */
/*   Updated: 2019/02/24 13:24:17 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list		*fd_find(int fd, t_list **nod)
{
	t_list			*temp;

	temp = *nod;
	while (temp)
	{
		if ((int)temp->content_size == fd)
			return (temp);
		temp = temp->next;
	}
	temp = ft_lstnew(NULL, 0);
	temp->content_size = (size_t)fd;
	temp->content = (void*)ft_strnew(1);
	ft_lstadd(nod, temp);
	return (temp);
}

static int			write_line(t_list **nod, char **line)
{
	char			*tmp1;

	if ((tmp1 = ft_strchr((*nod)->content, '\n')))
	{
		*line = ft_strsub((*nod)->content, 0, tmp1++ - (char *)(*nod)->content);
		tmp1 = ft_strdup(tmp1);
		free((*nod)->content);
		(*nod)->content = tmp1;
	}
	else if (*(char *)(*nod)->content)
	{
		*line = ft_strdup((char *)(*nod)->content);
		free((*nod)->content);
		(*nod)->content = NULL;
	}
	else
	{
		free((*nod)->content);
		(*nod)->content = NULL;
		return (0);
	}
	return (1);
}

int					get_next_line(const int fd, char **line)
{
	char			buff[BUFF_SIZE + 1];
	static t_list	*tmp;
	int				ret;
	t_list			*nod;

	if (fd < 0 || (read(fd, buff, 0)) || BUFF_SIZE < 1)
		return (-1);
	nod = fd_find(fd, &tmp);
	if (nod->content == NULL)
		return (0);
	while (!ft_strchr(nod->content, '\n') &&
			(ret = (int)read(fd, buff, BUFF_SIZE)))
	{
		buff[ret] = '\0';
		if (!(nod->content = ft_new_strjoin(nod->content, buff)))
			return (-1);
	}
	if (!ft_strlen((char *)nod->content))
		return (0);
	if (nod->content)
		return (write_line(&nod, &(*line)));
	free(nod->content);
	return (0);
}
