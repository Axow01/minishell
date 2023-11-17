/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:59:46 by mmarcott          #+#    #+#             */
/*   Updated: 2023/11/12 20:07:43 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libmms.h"

int	mms_open(char *path, int mode, int permission)
{
	t_mms_fd	*fd_mms;

	fd_mms = get_data_mms()->mms_fd;
	while (fd_mms && fd_mms->next)
		fd_mms = fd_mms->next;
	if (!fd_mms)
	{
		fd_mms = mms_alloc(1, sizeof(t_mms_fd));
		get_data_mms()->mms_fd = fd_mms;
	}
	else
	{
		fd_mms->next = mms_alloc(1, sizeof(t_mms_fd));
		fd_mms = fd_mms->next;
	}
	if (permission > 0)
		fd_mms->fd = open(path, mode, permission);
	else
		fd_mms->fd = open(path, mode);
	fd_mms->next = NULL;
	return (fd_mms->fd);
}

void	mms_close(int fd)
{
	t_mms_fd	*mms_fd;

	mms_fd = get_data_mms()->mms_fd;
	while (mms_fd)
	{
		if (mms_fd->fd == fd)
		{
			close(mms_fd->fd);
			mms_fd->fd = 0;
		}
		mms_fd = mms_fd->next;
	}
}

void	mms_clean_fd(void)
{
	t_mms_fd	*mms_fd;
	t_mms_fd	*temp;

	mms_fd = get_data_mms()->mms_fd;
	while (mms_fd)
	{
		if (mms_fd->fd > 0)
			close(mms_fd->fd);
		temp = mms_fd;
		mms_fd = mms_fd->next;
		temp = mms_free(temp);
	}
	get_data_mms()->mms_fd = NULL;
}

// void	mms_printfd()
// {
// 	t_mms_fd	*fd_mms;

// 	fd_mms = get_data_mms()->mms_fd;
// 	while (fd_mms)
// 	{
// 		printf("FD:%d NEXTPTR:%p\n", fd_mms->fd, fd_mms->next);
// 		fd_mms = fd_mms->next;
// 	}
// }
