/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_INTERNAL_H
# define MD5_INTERNAL_H

# include "ft.h"
# include "md5.h"

typedef struct s_md5_ctx    t_md5_ctx;
struct  s_md5_ctx
{
    struct s_buffer *buffer;
    uint32_t        v[4];
};

t_md5_ctx   md5_ctx_init(struct s_buffer *buffer);
void        md5_ctx_run(t_md5_ctx *ctx);
void        md5_ctx_print(const t_md5_ctx *ctx);

void	    md5_round1(const uint32_t *x, uint32_t v[4]);
void	    md5_round2(const uint32_t *x, uint32_t v[4]);
void	    md5_round3(const uint32_t *x, uint32_t v[4]);
void	    md5_round4(const uint32_t *x, uint32_t v[4]);

uint32_t	md5_f(const uint32_t b, const uint32_t c, const uint32_t d);
uint32_t	md5_g(const uint32_t b, const uint32_t c, const uint32_t d);
uint32_t	md5_h(const uint32_t b, const uint32_t c, const uint32_t d);
uint32_t	md5_i(const uint32_t b, const uint32_t c, const uint32_t d);

#endif