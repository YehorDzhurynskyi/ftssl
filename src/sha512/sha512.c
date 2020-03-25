/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha512.h"
#include "sha512_internal.h"
#include <assert.h> // TODO: remove

void    sha512_process(struct s_buffer *buffer)
{
    t_sha512_ctx   ctx;

    ctx = sha512_ctx_init(buffer);
    ctx.v[0] = 0x6a09e667f3bcc908;
    ctx.v[1] = 0xbb67ae8584caa73b;
    ctx.v[2] = 0x3c6ef372fe94f82b;
    ctx.v[3] = 0xa54ff53a5f1d36f1;
    ctx.v[4] = 0x510e527fade682d1;
    ctx.v[5] = 0x9b05688c2b3e6c1f;
    ctx.v[6] = 0x1f83d9abfb41bd6b;
    ctx.v[7] = 0x5be0cd19137e2179;
    assert(buffer->size == buffer->capacity);
    sha512_ctx_run(&ctx);
    sha512_ctx_print(&ctx);
}
