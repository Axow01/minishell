/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:50:52 by oboucher          #+#    #+#             */
/*   Updated: 2023/11/17 13:50:54 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif
//#define OPEN_MAX 1024

# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

//struct

typedef struct s_var
{
	char	*buffer;
	char	*next_line;
	int		rd;
	size_t	pos;
}			t_var;

//prototype

void		ft_gnl_bzero(void *b, size_t len);
void		*ft_sfree(void *str);
void		*ft_gnl_calloc(size_t count, size_t size);
size_t		ft_gnl_strlen(char *str);
char		*ft_gnl_strjoin(char *s1, char *s2);
char		*get_next_line(int fd);

#endif