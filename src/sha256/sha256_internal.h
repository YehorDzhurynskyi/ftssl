/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_INTERNAL_H
# define SHA256_INTERNAL_H

# include "ft.h"
# include "sha256.h"

typedef struct s_sha256_ctx t_sha256_ctx;
struct  s_sha256_ctx
{
    struct s_buffer *buffer;
    uint32_t        v[8];
};

t_sha256_ctx    sha256_ctx_init(struct s_buffer *buffer);
void            sha256_ctx_run(t_sha256_ctx *ctx);
void            sha256_ctx_print(const t_sha256_ctx *ctx);

#endif