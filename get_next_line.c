/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuslysty <vuslysty@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:42:11 by vuslysty          #+#    #+#             */
/*   Updated: 2018/11/11 12:41:32 by vuslysty         ###   ########.fr       */
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
	int				len;
	char			*str_buf;

	str_buf = (char*)list->content;
	i = 0;
	len = ft_strlen(str_buf);
	while (str_buf[++i] != '\0' && len--)
		if (str_buf[i] == '\n')
		{
			temp = *all_str;
			ft_strncpy(buf, str_buf, i);
			buf[i] = '\0';
			*all_str = ft_strjoin(temp, buf);
			free(temp);
			ft_strcpy(str_buf, str_buf + i + 1);
			return (1);
		}
	temp = *all_str;
	*all_str = ft_strjoin(temp, str_buf);
	free(temp);
	return (0);
}

t_list				*get_right_list(int fd, t_list *begin)
{
	t_list			*temp;
	char			*new;

	temp = begin;
	while (temp->next != NULL)
	{
		if (temp->content_size == fd)
			return (temp);
		temp = temp->next;
	}
	if (temp->content_size == fd)
		return (temp);
	else
		ft_lstadd_end(&begin, ft_listnew(fd));
	return (temp->next);
}

int					get_next_line(const int fd, char **line)
{
	static t_list	list = {"", -1, NULL};
	t_list			*temp;
	char			*all_str;
	int				rd;

	all_str = ft_strdup("");
	temp = get_right_list(fd, &list);
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
	return ((rd == 0) ? 0 : 1);
}

int					main(void)
{
	int				fd1;
	int				fd2;
	int				fd3;
	char			*str;

	fd1 = open("harry_potter.txt", O_RDONLY);
	fd2 = open("test1", O_RDONLY);
	fd3 = open("get_next_line.h", O_RDONLY);

	while (get_next_line(fd1, &str))
	{
		ft_putstr(str);
		ft_putchar('\n');
		free(str);
	}
	ft_putstr(str);
	ft_putchar('\n');

	while (get_next_line(fd2, &str))
    {
        ft_putstr(str);
        ft_putchar('\n');
        free(str);
    }
    ft_putstr(str);
    ft_putchar('\n');

	while (get_next_line(fd3, &str))
    {
        ft_putstr(str);
        ft_putchar('\n');
        free(str);
    }
    ft_putstr(str);
    ft_putchar('\n');
/*
	get_next_line(fd1, &str);
	ft_putstr(str);
	ft_putchar('\n');
	free(str);
	get_next_line(fd2, &str);
	ft_putstr(str);
	ft_putchar('\n');
	free(str);
	get_next_line(fd1, &str);
    ft_putstr(str);
    ft_putchar('\n');
    free(str);
	get_next_line(fd2, &str);
    ft_putstr(str);
    ft_putchar('\n');
    free(str);
	get_next_line(fd1, &str);
    ft_putstr(str);
    ft_putchar('\n');
    free(str);
	get_next_line(fd2, &str);
    ft_putstr(str);
    ft_putchar('\n');
    free(str);
	get_next_line(fd1, &str);
    ft_putstr(str);
    ft_putchar('\n');
    free(str);
*/
//	system("leaks a.out");
	return (0);
}
