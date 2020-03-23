/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_ctx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5_internal.h"
#include <assert.h> // TODO: remove

static uint32_t g_T[64] =
{
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,

        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,

        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,

        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

static uint32_t g_S[64] =
{
    7, 12, 17, 22,
    7, 12, 17, 22,
    7, 12, 17, 22,
    7, 12, 17, 22,

    5,  9, 14, 20,
    5,  9, 14, 20,
    5,  9, 14, 20,
    5,  9, 14, 20,

    4, 11, 16, 23,
    4, 11, 16, 23,
    4, 11, 16, 23,
    4, 11, 16, 23,

    6, 10, 15, 21,
    6, 10, 15, 21,
    6, 10, 15, 21,
    6, 10, 15, 21
};

#define HEX "0123456789abcdef"

void        md5_ctx_print(const t_md5_ctx *ctx)
{
    int     i;
    t_byte  b;

    i = -1;
    while (++i < 16)
    {
        b = *((t_byte*)ctx->v + i);
        ft_putchar(HEX[b / 16]);
        ft_putchar(HEX[b % 16]);
    }
}

t_md5_ctx   md5_ctx_init(struct s_buffer *buffer)
{
    t_md5_ctx   ctx;
    uint64_t	olen;
    uint64_t	len;
    int			zeroes_count;
    int			i;

    ctx.buffer = buffer;
    olen = ctx.buffer->size * CHAR_BIT;
    len = olen + 1;
    // TODO: figure out correctness of 'zeroes_count'
    // zeroes_count = MD5_PAYLOAD_BIT_SIZE - len % MD5_PAYLOAD_BIT_SIZE;
    zeroes_count = FT_ALIGN_UP(len, MD5_BLOCK_BIT_SIZE) - len - MD5_LEN_BIT_SIZE;
    len = (len / MD5_BLOCK_BIT_SIZE) * MD5_BLOCK_BIT_SIZE + MD5_PAYLOAD_BIT_SIZE;
    buffer_append(ctx.buffer, (t_byte*)"\x80", 1);
    i = 0;
    while (i++ < zeroes_count / CHAR_BIT)
        buffer_append(ctx.buffer, (t_byte*)"\x0", 1);
    buffer_append(ctx.buffer, (t_byte*)&olen, sizeof(uint64_t));
    ctx.v[0] = 0x67452301;
    ctx.v[1] = 0xefcdab89;
    ctx.v[2] = 0x98badcfe;
    ctx.v[3] = 0x10325476;
    return (ctx);
}

static uint32_t	rotl(const uint32_t v, uint32_t r)
{
    assert(r < 32);
    return ((v << r) | (v >> (32 - r)));
}

void        md5_ctx_run(t_md5_ctx *ctx)
{
    int i;
    int j;
    assert(ctx->buffer->size % MD5_BLOCK_SIZE == 0);

    i = -1;
    while (++i < ctx->buffer->size / MD5_BLOCK_SIZE)
    {
        uint32_t v[4];

        ft_memcpy(&v, ctx->v, sizeof(v));

        uint32_t f;
        uint32_t g;
        j = -1;
        while (++j < 64)
        {
            if (j >= 0 && j < 16)
            {
                f = md5_f(v[1], v[2], v[3]);
                g = j;
            }
            else if (j >= 16 && j < 32)
            {
                f = md5_g(v[1], v[2], v[3]);
                g = (5 * j + 1) % 16;
            }
            else if (j >= 32 && j < 48)
            {
                f = md5_h(v[1], v[2], v[3]);
                g = (3 * j + 5) % 16;
            }
            else if (j >= 48 && j < 64)
            {
                f = md5_i(v[1], v[2], v[3]);
                g = (7 * j) % 16;
            }
            uint32_t *m = (uint32_t*)(buffer_data(ctx->buffer) + i * MD5_BLOCK_SIZE);
            f += v[0] + g_T[j] + m[g];

            v[0] = v[3];
            v[3] = v[2];
            v[2] = v[1];
            v[1] += rotl(f, g_S[j]);
        }
        ctx->v[0] += v[0];
        ctx->v[1] += v[1];
        ctx->v[2] += v[2];
        ctx->v[3] += v[3];
    }
}
