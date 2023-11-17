/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:46:41 by oboucher          #+#    #+#             */
/*   Updated: 2023/11/17 13:46:43 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/list.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*temp;

	count = 1;
	temp = lst;
	if (!lst)
		return (0);
	while (temp->next != NULL)
	{
		temp = temp->next;
		count++;
	}
	return (count);
}
