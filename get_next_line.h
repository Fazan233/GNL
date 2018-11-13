/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuslysty <vuslysty@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:42:46 by vuslysty          #+#    #+#             */
/*   Updated: 2018/11/12 16:36:24 by vuslysty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 32
# include <sys/types.h>
# include <sys/uio.h>
# include "libft.h"

int		get_next_line(const int fd, char **line);
t_list	*get_right_list(int fd, t_list *begin);
int		is_endline(t_list *list, char **all_str);
t_list	*ft_listnew(int fd);
int		validator(t_list *list, char **all_str);

#endif
