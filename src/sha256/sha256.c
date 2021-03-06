/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"
#include "sha256_internal.h"
#include <assert.h> // TODO: remove

void    sha256_process(struct s_buffer *buffer)
{
    t_sha256_ctx   ctx;

    assert(buffer->capacity % SHA256_BLOCK_SIZE == 0);
    ctx = sha256_ctx_init(buffer);
    ctx.v[0] = 0x6a09e667;
    ctx.v[1] = 0xbb67ae85;
    ctx.v[2] = 0x3c6ef372;
    ctx.v[3] = 0xa54ff53a;
    ctx.v[4] = 0x510e527f;
    ctx.v[5] = 0x9b05688c;
    ctx.v[6] = 0x1f83d9ab;
    ctx.v[7] = 0x5be0cd19;
    assert(buffer->size == buffer->capacity);
    sha256_ctx_run(&ctx);
    sha256_ctx_print(&ctx);
}
