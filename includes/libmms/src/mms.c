/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mms.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:51:32 by mmarcott          #+#    #+#             */
/*   Updated: 2023/11/17 14:14:28 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libmms.h"

t_pointer	*get_data_mms(void)
{
	static t_pointer	*data = NULL;

	if (!data)
	{
		data = ft_calloc(1, sizeof(t_pointer));
		if (!data)
			mms_kill("Failled to allocate ! \n", true, EXIT_FAILURE);
		data->f = NULL;
		data->next = NULL;
		data->ptr = NULL;
		data->initiated = false;
		data->last_allocated = data;
	}
	return (data);
}

void	mms_kill(char *message, bool quit, int code)
{
	t_pointer	*current;
	t_pointer	*buffer;

	current = get_data_mms();
	mms_clean_fd();
	while (current)
	{
		if (current->ptr)
			free(current->ptr);
		current->ptr = NULL;
		buffer = current->next;
		free(current);
		current = buffer;
	}
	if (message)
		printf("%s", message);
	if (quit)
		exit(code);
}

void	*mms_alloc(size_t size, size_t typesize)
{
	t_pointer	*current;

	if (size <= 0)
		size = 1;
	if (!get_data_mms()->ptr && !get_data_mms()->initiated)
	{
		get_data_mms()->initiated = true;
		current = get_data_mms();
		current->ptr = (get_data_mms()->f(size, typesize));
		if (!get_data_mms()->ptr)
			mms_kill("Failled to allocate ! \n", true, EXIT_FAILURE);
		get_data_mms()->next = NULL;
		get_data_mms()->last_allocated = current;
		return (get_data_mms()->ptr);
	}
	current = get_data_mms()->last_allocated;
	current->next = get_data_mms()->f(1, sizeof(t_pointer));
	if (!current->next)
		mms_kill("Allocation Error\n", true, 10);
	current = current->next;
	current->ptr = get_data_mms()->f(size, typesize);
	if (!current->ptr)
		mms_kill("Allocation Error\n", true, 10);
	get_data_mms()->last_allocated = current;
	return (current->ptr);
}

void	*mms_free(void *ptr)
{
	t_pointer	*current;

	current = get_data_mms();
	while (current)
	{
		if (current->ptr == ptr)
		{
			free(current->ptr);
			current->ptr = NULL;
			return (NULL);
		}
		current = current->next;
	}
	return (NULL);
}

void	print_list(void)
{
	t_pointer	*current;

	current = get_data_mms();
	if (!current)
		return ;
	while (current)
	{
		if (current->ptr)
			printf("%p\n", current->ptr);
		else
			write(1, "NULL\n", 5);
		current = current->next;
	}
}
