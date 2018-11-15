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
# include "libft/libft.h"
# define F_CLOSE {ft_bzero(temp->content, BUFF_SIZE);return(-1);}
# define END_OR_OK {return((rd == 0 && **line == '\0') ? 0 : 1);}
# define GNL_RETURN(rd) if(rd == -1){F_CLOSE}else{END_OR_OK}
# define VALID_LIST(list) if(!list){free(all_str);return(-1);}

int		get_next_line(const int fd, char **line);

#endif
