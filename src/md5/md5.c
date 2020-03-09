/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include "assert.h"

static void	append32(struct s_buffer *buff, const unsigned int bits)
{
	int		i;
	t_byte	byte;

	i = 32 / CHAR_BIT - 1;
	while (i >= 0)
	{
		byte = (bits >> i-- * CHAR_BIT) & 0xff;
		buffer_append(buff, &byte, 1);
	}
}

void		md5_digest(struct s_buffer *buff, char *out)
{
	unsigned long long	len;
	int					zeroes_count;
	int					i;
	unsigned int		iv[4];

	(void)out;
	assert(buff->capacity % MD5_BLOCK_SIZE == 0);
	len = buff->size * CHAR_BIT + 1;
	zeroes_count = MD5_PAYLOAD_BIT_SIZE - len % MD5_PAYLOAD_BIT_SIZE;
	len = (len / MD5_BLOCK_BIT_SIZE) *
	MD5_BLOCK_BIT_SIZE + MD5_PAYLOAD_BIT_SIZE;
	buffer_append(buff, (t_byte*)"\x80", 1);
	i = 0;
	while (i++ < zeroes_count / CHAR_BIT)
	{
		buffer_append(buff, (t_byte*)"\x0", 1);
	}
	append32(buff, len & UINT_MAX);
	append32(buff, (len >> 32) & UINT_MAX);
	assert(buff->size == buff->capacity);
	assert(buff->size % MD5_BLOCK_SIZE == 0);
	iv[0] = 0x67 << 24 | 0x45 << 16 | 0x23 << 8 | 0x01 << 0;
	iv[1] = 0xEF << 24 | 0xCD << 16 | 0xAB << 8 | 0x89 << 0;
	iv[2] = 0x98 << 24 | 0xBA << 16 | 0xDC << 8 | 0xFE << 0;
	iv[3] = 0x10 << 24 | 0x32 << 16 | 0x54 << 8 | 0x76 << 0;
}

void		md5_process(const t_byte *buffer, const size_t size)
{
	(void)buffer;
	(void)size;
	ft_printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
}
