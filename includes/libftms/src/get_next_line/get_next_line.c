/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:41:12 by oboucher          #+#    #+#             */
/*   Updated: 2023/11/17 13:41:14 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/get_next_line.h"
#include "../../../libmms/libmms.h"

static size_t	ft_find(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_small_split(char *line, size_t *pos)
{
	char	*fnext_line;
	size_t	i;

	i = 0;
	while (line[i])
		if (line[i++] == '\n')
			break ;
	*pos = i;
	fnext_line = mms_alloc(i + 1, sizeof(char));
	if (!fnext_line)
		return (mms_free(fnext_line));
	while (i--)
		fnext_line[i] = line[i];
	return (fnext_line);
}

static int	init_check(int fd, t_var *var)
{
	var->rd = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX || read(fd, &var->buffer,
			0) < 0)
		return (0);
	return (1);
}

/// @brief get the next line in a file
/// @param fd is a file descriptor 
/// @return the next line
char	*get_next_line(int fd)
{
	static char	*line[OPEN_MAX];
	t_var		var;

	if (init_check(fd, &var) == 0)
		return (line[fd] = ft_sfree(line[fd]), NULL);
	if (!line[fd])
		line[fd] = mms_alloc(1, sizeof(char));
	var.buffer = mms_alloc(BUFFER_SIZE + 1, sizeof(char));
	var.pos = 0;
	while (ft_find(line[fd]) == 0)
	{
		ft_gnl_bzero(var.buffer, BUFFER_SIZE + 1);
		var.rd = read(fd, var.buffer, BUFFER_SIZE);
		if (var.rd <= 0)
			break ;
		line[fd] = ft_gnl_strjoin(line[fd], var.buffer);
	}
	var.buffer = mms_free(var.buffer);
	if (var.rd == -1 || (var.rd <= 0 && *line[fd] == 0))
		return (line[fd] = mms_free(line[fd]), NULL);
	var.next_line = ft_small_split(line[fd], &var.pos);
	var.buffer = line[fd];
	line[fd] = ft_gnl_strjoin(NULL, line[fd] + var.pos);
	return (var.buffer = mms_free(var.buffer), var.next_line);
}
