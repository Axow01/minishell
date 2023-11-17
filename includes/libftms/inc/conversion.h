/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:49:51 by oboucher          #+#    #+#             */
/*   Updated: 2023/11/17 13:49:53 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERSION_H
# define CONVERSION_H

//prototype

int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
long int	ft_atoli(const char *str);

#endif