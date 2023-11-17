/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmms.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:48:36 by mmarcott          #+#    #+#             */
/*   Updated: 2023/11/17 14:14:12 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMMS_H
# define LIBMMS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdarg.h>
# include "../libftms/inc/libft.h"

typedef struct s_mms_fd
{
	int				fd;
	struct s_mms_fd	*next;
}				t_mms_fd;

typedef struct s_pointer
{
	void				*ptr;
	struct s_pointer	*next;
	void				*(*f)(size_t, size_t);
	void				*last_allocated;
	t_mms_fd			*mms_fd;
	bool				initiated;
}				t_pointer;

/// @brief This function deletes all the pointers assigned with the lib.
/// @param message The message to print when quitting.
/// @param quit Quitting of not.
/// @param code The exit code when quitting.
void		mms_kill(char *message, bool quit, int code);

/// @brief Allocate memory.
/// @param size the size in bytes.
/// @param typesize The type size in bytes.
/// @return An allocated pointer.
void		*mms_alloc(size_t size, size_t typesize);

/// @brief Prints the pointers list.
void		print_list(void);

/// @brief Frees a single pointer allocated with the lib.
/// @param ptr The pointer to free.
/// @return NULL in all cases.
void		*mms_free(void *ptr);

/// @brief Do not use for your project, this function is used 
//				to get the structure of the lib.
/// @return The lib's structure.
t_pointer	*get_data_mms(void);

/// @brief Used to change the default function for allocation.
/// @param f The function ex: calloc. Default is calloc.
void		mms_set_alloc_fn(void *(*f)(size_t, size_t));

/// @brief This function allows the user to add a pointer not created by the lib
///			to the system. exemple: read(), readline(), etc. All function that
///			return ptr that needs to free eventually.
/// @param ptr Any pointer to store. Cannot be a pointer already stored
///				by the lib.
/// @return True if the ptr was added to the lib, false if not.
bool		mms_add_ptr(void *ptr);

/// @brief This removes a pointer from the lib tracking system.
/// @param ptr the ptr to remove.
/// @return True if succeeded, false if not.
bool		mms_untrack_ptr(void *ptr);

/// @brief Removes all fd and frees the struct.
void		mms_clean_fd(void);

/// @brief Close and fd, opened with the mms lib.
/// @param fd 
void		mms_close(int fd);

/// @brief This open a file, like the open function.
/// @param path 
/// @param mode 
/// @param permission 
int			mms_open(char *path, int mode, int permission);

#endif
