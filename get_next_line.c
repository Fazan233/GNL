/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuslysty <vuslysty@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:42:11 by vuslysty          #+#    #+#             */
/*   Updated: 2018/11/11 21:41:24 by vuslysty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <fcntl.h>
#include "get_next_line.h"

t_list*				ft_listnew(int fd)
{
	t_list			*list;

	list = (t_list*)ft_memalloc(sizeof(t_list));
	if (list)
	{
		list->next = NULL;
		list->content = (char*)ft_memalloc(BUFF_SIZE + 1);
		if (list->content)
			list->content_size = fd;
		else
		{
			free(list);
			return (NULL);
		}
	}
	return (list);
}

int					is_endline(t_list *list, char **all_str)
{
	int				i;
	char			*temp;
	char			buf[BUFF_SIZE + 1];
	char			*str_buf;

	str_buf = (char*)list->content;
	i = -1;
	temp = *all_str;
	while (str_buf[++i] != '\0')
		if (str_buf[i] == '\n')
		{
			ft_strncpy(buf, str_buf, i);
			buf[i] = '\0';
			*all_str = ft_strjoin(temp, buf);
			free(temp);
			ft_strcpy(str_buf, str_buf + i + 1);
			return (1);
		}
	*all_str = ft_strjoin(temp, str_buf);
	free(temp);
	ft_bzero(list->content, BUFF_SIZE);
	return (0);
}

t_list				*get_right_list(int fd, t_list *begin)
{
	t_list			*temp;

	temp = begin;
	while (temp->next != NULL)
	{
		if ((int)temp->content_size == fd)
			return (temp);
		temp = temp->next;
	}
	if ((int)temp->content_size == fd)
		return (temp);
	else
		ft_lstadd_end(&begin, ft_listnew(fd));
	return (temp->next);
}

int					validator(t_list *list, char **all_str)
{
	int				rd;
	int				fd;
	char			buf[1];
	t_list			*temp;

	fd = (int)list->content_size;
	if (fd >= 0)
	{
		rd = read(fd, buf, 1);
		if (rd == 1 || rd == 0)
		{
			((char*)list->content)[ft_strlen(((char*)list->content))] = *buf;
			((char*)list->content)[ft_strlen(((char*)list->content)) + 1] = '\0';
			return ((rd == 0) ? 1 : 0);
		}
		else
		{
			ft_strdel(all_str);
			temp = list->next;
			free(list->content);
			free(list);
			list = temp;
		}
	}
	return (-1);
}

int					get_next_line(const int fd, char **line)
{
	static t_list	list = {"", -1, NULL};
	t_list			*temp;
	char			*all_str;
	int				rd;
	int				valid;

	all_str = ft_strdup("");
	temp = get_right_list(fd, &list);
	valid = validator(temp, &all_str);
	if (((char*)(temp->content))[0] == '\0')
		if (valid)
			return ((valid == 1) ? 0 : -1);
	if (is_endline(temp , &all_str))
	{
		*line = all_str;
		return (1);
	}
	while ((rd = read(fd, (char*)temp->content, BUFF_SIZE)))
	{
		((char*)temp->content)[rd] = '\0';
		if (is_endline(temp, &all_str))
			break ;
	}
	*line = all_str;
	return ((rd == 0 && **line == '\0') ? 0 : 1);
}
