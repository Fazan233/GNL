/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuslysty <vuslysty@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:42:11 by vuslysty          #+#    #+#             */
/*   Updated: 2018/11/10 18:43:07 by vuslysty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <fcntl.h>
#include "get_next_line.h"

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

t_list				*get_right_list(int fd, t_list *list)
{
	t_list			*begin;

	begin = list;
	
	while (list->next != NULL)
	{
		if (list->content_size == fd)
			return (list);
		list = list->next;
	}
	if (list->content_size == fd)
		return (list);
	else
		ft_lstadd_end(&begin, ft_lstnew(NULL, fd));
	return (begin);
}

int					get_next_line(const int fd, char **line)
{
	static t_list	list = {NULL, 1, NULL};
	t_list			*temp;
	char			*all_str;
	int				rd;

	all_str = ft_strdup("");
	temp = get_right_list(fd, &list);
	
	if (temp->content)
	{
		if (is_endline(temp , &all_str))
		{
			*line = all_str;
			return (1);
		}
	}
	else
		temp->content = (char*)ft_memalloc(BUFF_SIZE + 1);
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
	char			*str;

	fd1 = open("test1", O_RDONLY);
	fd2 = open("test2", O_RDONLY);
/*	while (get_next_line(fd, &str))
	{
		ft_putstr(str);
		ft_putchar('\n');
		free(str);
	}
	ft_putstr(str);
	ft_putchar('\n');
*/
	get_next_line(fd1, &str);
	ft_putstr(str);
	ft_putchar('\n');
	free(str);
	get_next_line(fd2, &str);
	ft_putstr(str);
	ft_putchar('\n');
	free(str);

//	system("leaks a.out");
	return (0);
}
