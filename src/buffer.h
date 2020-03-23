/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H

# include "ft.h"
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <limits.h>

# define SBO_SIZE (64)

struct s_buffer
{
	union
	{
		t_byte	*dynamic;
		t_byte	sbo[SBO_SIZE];
	} data;
	size_t	capacity;
	size_t	size;
	int		multiplier;
};

struct s_buffer	buffer_create(const int multiplier);
void			buffer_free(struct s_buffer* buff);
void			buffer_append(struct s_buffer *buff,
const t_byte *src, const size_t len);
t_byte			*buffer_data(const struct s_buffer *buff);
t_bool			buffer_read_fd(struct s_buffer *buff, const int fd);

#endif
