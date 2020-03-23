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
    assert(buffer->size == buffer->capacity);
    sha256_ctx_run(&ctx);
    sha256_ctx_print(&ctx);
}
