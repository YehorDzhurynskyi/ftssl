/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA512_INTERNAL_H
# define SHA512_INTERNAL_H

# include "ft.h"
# include "sha512.h"

typedef struct s_sha512_ctx t_sha512_ctx;
struct  s_sha512_ctx
{
    struct s_buffer *buffer;
    uint64_t        v[8];
};

t_sha512_ctx    sha512_ctx_init(struct s_buffer *buffer);
void            sha512_ctx_run(t_sha512_ctx *ctx);
void            sha512_ctx_print(const t_sha512_ctx *ctx);

#endif