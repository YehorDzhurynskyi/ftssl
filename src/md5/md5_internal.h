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

void	md5_round1(const unsigned int *x, unsigned int v[4]);
void	md5_round2(const unsigned int *x, unsigned int v[4]);
void	md5_round3(const unsigned int *x, unsigned int v[4]);
void	md5_round4(const unsigned int *x, unsigned int v[4]);

t_byte	md5_f(const t_byte a, const t_byte b, const t_byte c);
t_byte	md5_g(const t_byte a, const t_byte b, const t_byte c);
t_byte	md5_h(const t_byte a, const t_byte b, const t_byte c);
t_byte	md5_i(const t_byte a, const t_byte b, const t_byte c);

#endif