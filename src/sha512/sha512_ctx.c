/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_ctx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha512_internal.h"
#include <assert.h> // TODO: remove

static const uint64_t g_K[80] =
{
    0x428a2f98d728ae22, 0x7137449123ef65cd,
    0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
    0x3956c25bf348b538, 0x59f111f1b605d019,
    0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
    0xd807aa98a3030242, 0x12835b0145706fbe,
    0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
    0x72be5d74f27b896f, 0x80deb1fe3b1696b1,
    0x9bdc06a725c71235, 0xc19bf174cf692694,
    0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
    0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
    0x2de92c6f592b0275, 0x4a7484aa6ea6e483,
    0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
    0x983e5152ee66dfab, 0xa831c66d2db43210,
    0xb00327c898fb213f, 0xbf597fc7beef0ee4,
    0xc6e00bf33da88fc2, 0xd5a79147930aa725,
    0x06ca6351e003826f, 0x142929670a0e6e70,
    0x27b70a8546d22ffc, 0x2e1b21385c26c926,
    0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
    0x650a73548baf63de, 0x766a0abb3c77b2a8,
    0x81c2c92e47edaee6, 0x92722c851482353b,
    0xa2bfe8a14cf10364, 0xa81a664bbc423001,
    0xc24b8b70d0f89791, 0xc76c51a30654be30,
    0xd192e819d6ef5218, 0xd69906245565a910,
    0xf40e35855771202a, 0x106aa07032bbd1b8,
    0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
    0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
    0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
    0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
    0x748f82ee5defb2fc, 0x78a5636f43172f60,
    0x84c87814a1f0ab72, 0x8cc702081a6439ec,
    0x90befffa23631e28, 0xa4506cebde82bde9,
    0xbef9a3f7b2c67915, 0xc67178f2e372532b,
    0xca273eceea26619c, 0xd186b8c721c0c207,
    0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
    0x06f067aa72176fba, 0x0a637dc5a2c898a6,
    0x113f9804bef90dae, 0x1b710b35131c471b,
    0x28db77f523047d84, 0x32caab7b40c72493,
    0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
    0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
    0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

#define HEX "0123456789abcdef"

void        sha512_ctx_print(const t_sha512_ctx *ctx)
{
    int i;

    i = -1;
    while (++i < 8)
        ft_printf("%016llx", ctx->v[i]);
}

t_sha512_ctx    sha512_ctx_init(struct s_buffer *buffer)
{
    t_sha512_ctx    ctx;
    uint64_t	    olen;
    uint64_t	    len;
    int			    zeroes_count;
    int			    i;

    ctx.buffer = buffer;
    olen = ctx.buffer->size * CHAR_BIT;
    len = olen + 1;
    zeroes_count = FT_ALIGN_UP(len, SHA512_BLOCK_BIT_SIZE) - len - SHA512_LEN_BIT_SIZE;
    assert((olen + 1 + zeroes_count + SHA512_LEN_BIT_SIZE) % SHA512_BLOCK_BIT_SIZE == 0);
    len = (len / SHA512_BLOCK_BIT_SIZE) * SHA512_BLOCK_BIT_SIZE + SHA512_PAYLOAD_BIT_SIZE;
    buffer_append(ctx.buffer, (t_byte*)"\x80", 1);
    i = -1;
    while (++i < zeroes_count / CHAR_BIT)
        buffer_append(ctx.buffer, (t_byte*)"\x0", 1);
    i = 0;
    while (++i < 17)
    {
        const t_byte b = (olen >> (SHA512_LEN_BIT_SIZE - i * 16)) & 0xff;
        buffer_append(ctx.buffer, &b, 1);
    }
    return (ctx);
}

static uint64_t	rotr(const uint64_t v, uint64_t r)
{
    assert(r < 64);
    return ((v >> r) | (v << (64 - r)));
}

void        sha512_ctx_run(t_sha512_ctx *ctx)
{
    int i;
    int j;
    assert(ctx->buffer->size % SHA512_BLOCK_SIZE == 0);

    i = -1;
    while (++i < ctx->buffer->size / SHA512_BLOCK_SIZE)
    {
        uint64_t w[80];

        uint64_t *m = (uint64_t*)(buffer_data(ctx->buffer) + i * SHA512_BLOCK_SIZE);
        j = -1;
        while (++j < 16)
        {
            const uint64_t b0 = (m[j] & 0x00000000000000ff) << 56u;
            const uint64_t b1 = (m[j] & 0x000000000000ff00) << 40u;
            const uint64_t b2 = (m[j] & 0x0000000000ff0000) << 24u;
            const uint64_t b3 = (m[j] & 0x00000000ff000000) << 8u;
            const uint64_t b4 = (m[j] & 0x000000ff00000000) >> 8u;
            const uint64_t b5 = (m[j] & 0x0000ff0000000000) >> 24u;
            const uint64_t b6 = (m[j] & 0x00ff000000000000) >> 40u;
            const uint64_t b7 = (m[j] & 0xff00000000000000) >> 56u;

            w[j] = b0 | b1 | b2 | b3 | b4 | b5 | b6 | b7;
        }
        j = 15;
        while (++j < 80)
        {
            const uint64_t s0 = rotr(w[j - 15], 1) ^ rotr(w[j - 15], 8) ^ (w[j - 15] >> 7);
            const uint64_t s1 = rotr(w[j - 2], 19) ^ rotr(w[j - 2], 61) ^ (w[j - 2] >> 6);
            w[j] = w[j - 16] + s0 + w[j - 7] + s1;
        }

        uint64_t v[8];

        ft_memcpy(&v, ctx->v, sizeof(v));

        j = -1;
        while (++j < 80)
        {
            const uint64_t s1 = rotr(v[4], 14) ^ rotr(v[4], 18) ^ rotr(v[4], 41);
            const uint64_t ch = (v[4] & v[5]) ^ (~v[4] & v[6]);
            const uint64_t temp1 = v[7] + s1 + ch + g_K[j] + w[j];
            const uint64_t s0 = rotr(v[0], 28) ^ rotr(v[0], 34) ^ rotr(v[0], 39);
            const uint64_t maj = (v[0] & v[1]) ^ (v[0] & v[2]) ^ (v[1] & v[2]);
            const uint64_t temp2 = s0 + maj;

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
