/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha224.h"
#include "sha256/sha256_internal.h"
#include <assert.h> // TODO: remove

static void sha224_ctx_print(const t_sha256_ctx *ctx)
{
    int i;

    i = -1;
    while (++i < 7)
        ft_printf("%08x", ctx->v[i]);
}

void        sha224_process(struct s_buffer *buffer)
{
    t_sha256_ctx   ctx;

    assert(buffer->capacity % SHA224_BLOCK_SIZE == 0);
    ctx = sha256_ctx_init(buffer);
    ctx.v[0] = 0xc1059ed8;
    ctx.v[1] = 0x367cd507;
    ctx.v[2] = 0x3070dd17;
    ctx.v[3] = 0xf70e5939;
    ctx.v[4] = 0xffc00b31;
    ctx.v[5] = 0x68581511;
    ctx.v[6] = 0x64f98fa7;
    ctx.v[7] = 0xbefa4fa4;
    assert(buffer->size == buffer->capacity);
    sha256_ctx_run(&ctx);
    sha224_ctx_print(&ctx);
}
