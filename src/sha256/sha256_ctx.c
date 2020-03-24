/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_ctx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256_internal.h"
#include <assert.h> // TODO: remove

static const uint32_t g_K[64] =
{
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,

    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,

    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,

    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,

    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,

    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,

    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,

    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

#define HEX "0123456789abcdef"

void        sha256_ctx_print(const t_sha256_ctx *ctx)
{
    int i;

    i = -1;
    while (++i < 8)
        ft_printf("%08x", ctx->v[i]);
}

t_sha256_ctx    sha256_ctx_init(struct s_buffer *buffer)
{
    t_sha256_ctx    ctx;
    uint64_t	olen;
    uint64_t	len;
    int			zeroes_count;
    int			i;

    ctx.buffer = buffer;
    olen = ctx.buffer->size * CHAR_BIT;
    len = olen + 1;
    zeroes_count = FT_ALIGN_UP(len, SHA256_BLOCK_BIT_SIZE) - len - SHA256_LEN_BIT_SIZE;
    assert((olen + 1 + zeroes_count + 64) % 512 == 0);
    len = (len / SHA256_BLOCK_BIT_SIZE) * SHA256_BLOCK_BIT_SIZE + SHA256_PAYLOAD_BIT_SIZE;
    buffer_append(ctx.buffer, (t_byte*)"\x80", 1);
    i = -1;
    while (++i < zeroes_count / CHAR_BIT)
        buffer_append(ctx.buffer, (t_byte*)"\x0", 1);
    i = 0;
    while (++i < 9)
    {
        const t_byte b = (olen >> (64 - i * 8)) & 0xff;
        buffer_append(ctx.buffer, &b, 1);
    }
    ctx.v[0] = 0x6a09e667;
    ctx.v[1] = 0xbb67ae85;
    ctx.v[2] = 0x3c6ef372;
    ctx.v[3] = 0xa54ff53a;
    ctx.v[4] = 0x510e527f;
    ctx.v[5] = 0x9b05688c;
    ctx.v[6] = 0x1f83d9ab;
    ctx.v[7] = 0x5be0cd19;
    return (ctx);
}

static uint32_t	rotr(const uint32_t v, uint32_t r)
{
    assert(r < 32);
    return ((v >> r) | (v << (32 - r)));
}

void        sha256_ctx_run(t_sha256_ctx *ctx)
{
    int i;
    int j;
    assert(ctx->buffer->size % SHA256_BLOCK_SIZE == 0);

    i = -1;
    while (++i < ctx->buffer->size / SHA256_BLOCK_SIZE)
    {
        uint32_t w[64];

        uint32_t *m = (uint32_t*)(buffer_data(ctx->buffer) + i * SHA256_BLOCK_SIZE);
        j = -1;
        while (++j < 16)
        {
            const uint32_t b0 = (m[j] & 0x000000ff) << 24u;
            const uint32_t b1 = (m[j] & 0x0000ff00) << 8u;
            const uint32_t b2 = (m[j] & 0x00ff0000) >> 8u;
            const uint32_t b3 = (m[j] & 0xff000000) >> 24u;

            w[j] = b0 | b1 | b2 | b3;
        }
        j = 15;
        while (++j < 64)
        {
            const uint32_t s0 = rotr(w[j - 15], 7) ^ rotr(w[j - 15], 18) ^ (w[j - 15] >> 3);
            const uint32_t s1 = rotr(w[j - 2], 17) ^ rotr(w[j - 2], 19) ^ (w[j - 2] >> 10);
            w[j] = w[j - 16] + s0 + w[j - 7] + s1;
        }

        uint32_t v[8];

        ft_memcpy(&v, ctx->v, sizeof(v));

        j = -1;
        while (++j < 64)
        {
            const uint32_t s1 = rotr(v[4], 6) ^ rotr(v[4], 11) ^ rotr(v[4], 25);
            const uint32_t ch = (v[4] & v[5]) ^ (~v[4] & v[6]);
            const uint32_t temp1 = v[7] + s1 + ch + g_K[j] + w[j];
            const uint32_t s0 = rotr(v[0], 2) ^ rotr(v[0], 13) ^ rotr(v[0], 22);
            const uint32_t maj = (v[0] & v[1]) ^ (v[0] & v[2]) ^ (v[1] & v[2]);
            const uint32_t temp2 = s0 + maj;

            v[7] = v[6];
            v[6] = v[5];
            v[5] = v[4];
            v[4] = v[3] + temp1;
            v[3] = v[2];
            v[2] = v[1];
            v[1] = v[0];
            v[0] = temp1 + temp2;
        }

        ctx->v[0] += v[0];
        ctx->v[1] += v[1];
        ctx->v[2] += v[2];
        ctx->v[3] += v[3];
        ctx->v[4] += v[4];
        ctx->v[5] += v[5];
        ctx->v[6] += v[6];
        ctx->v[7] += v[7];
    }
}
