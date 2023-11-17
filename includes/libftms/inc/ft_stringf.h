/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stringf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:50:45 by oboucher          #+#    #+#             */
/*   Updated: 2023/11/17 13:50:47 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRINGF_H
# define FT_STRINGF_H

# include "conversion.h"
# include "error.h"
# include "get_next_line.h"
# include "memory.h"
# include "string.h"
# include <stdarg.h>
# include <unistd.h>

// prototype

char	*ft_stringf(const char *str, ...);
char	*sort_cs(char *val, char *str, size_t i);

#endif