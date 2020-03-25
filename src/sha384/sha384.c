/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha384.h"
#include "sha512/sha512_internal.h"
#include <assert.h> // TODO: remove

static void sha384_ctx_print(const t_sha512_ctx *ctx)
{
    int i;

    i = -1;
    while (++i < 6)
        ft_printf("%016llx", ctx->v[i]);
}

void        sha384_process(struct s_buffer *buffer)
{
    t_sha512_ctx   ctx;

    ctx = sha512_ctx_init(buffer);
    ctx.v[0] = 0xcbbb9d5dc1059ed8;
    ctx.v[1] = 0x629a292a367cd507;
    ctx.v[2] = 0x9159015a3070dd17;
    ctx.v[3] = 0x152fecd8f70e5939;
    ctx.v[4] = 0x67332667ffc00b31;
    ctx.v[5] = 0x8eb44a8768581511;
    ctx.v[6] = 0xdb0c2e0d64f98fa7;
    ctx.v[7] = 0x47b5481dbefa4fa4;
    assert(buffer->size == buffer->capacity);
    sha512_ctx_run(&ctx);
    sha384_ctx_print(&ctx);
}
