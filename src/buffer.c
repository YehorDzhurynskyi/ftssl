/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "assert.h"
#include <unistd.h>
#include <stdio.h>

struct s_buffer	buffer_create(const int multiplier)
{
	struct s_buffer buff;

	assert(multiplier && !(multiplier & (multiplier - 1)));
	assert(SBO_SIZE && !(SBO_SIZE & (SBO_SIZE - 1)));
	buff = (struct s_buffer){};
	buff.multiplier = multiplier;
	buff.capacity = SBO_SIZE;
	return buff;
}

void			buffer_free(struct s_buffer* buff)
{
	if (buff->size > SBO_SIZE)
	{
		free(buff->data.dynamic);
	}
}

static void		buffer_realloc(struct s_buffer *buff,
const t_byte *src, const size_t capacity)
{
	t_byte	*temp;

	temp = malloc(capacity);
	ft_memcpy(temp, src, buff->size);
	if (buff->size > SBO_SIZE)
	{
		free(buff->data.dynamic);
	}
	buff->capacity = capacity;
	buff->data.dynamic = temp;
}

void			buffer_append(struct s_buffer *buff,
const t_byte *src, const size_t len)
{
	t_byte	*dest;
	size_t	required_capacity;

	if (buff->size + len <= SBO_SIZE)
	{
		dest = buff->data.sbo + buff->size;
	}
	else
	{
		required_capacity = sizeof(t_byte) *
		ft_ceil((buff->size + len) / (float)buff->multiplier) *
		buff->multiplier;
		if (buff->size <= SBO_SIZE)
		{
			buffer_realloc(buff, buff->data.sbo, required_capacity);
		}
		else if (buff->size + len > buff->capacity)
		{
			buffer_realloc(buff, buff->data.dynamic, required_capacity);
		}
		dest = buff->data.dynamic + buff->size;
	}
	ft_memcpy(dest, src, len);
	buff->size += len;
}

t_byte			*buffer_data(const struct s_buffer *buff)
{
	return buff->size > SBO_SIZE ? buff->data.dynamic : (t_byte*)buff->data.sbo;
}

ssize_t			buffer_read_fd(struct s_buffer *buff, const int fd)
{
	ssize_t	len;
	t_byte	temp[1024];

	assert(fd >= 0);
	while ((len = read(fd, temp, sizeof(temp))) > 0)
	{
		buffer_append(buff, temp, len);
	}
	if (len < 0)
	{
		perror(NULL);
	}
	return (len);
}
