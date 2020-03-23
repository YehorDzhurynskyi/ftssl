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
#include "md5_internal.h"
#include "assert.h" // TODO: remove

void		md5_process(struct s_buffer *buffer)
{
	t_md5_ctx   ctx;

    assert(buffer->capacity % MD5_BLOCK_SIZE == 0);
    ctx = md5_ctx_init(buffer);
	assert(buffer->size == buffer->capacity);
    md5_ctx_run(&ctx);
    md5_ctx_print(&ctx);
}
