/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

uint32_t	md5_f(const uint32_t b, const uint32_t c, const uint32_t d)
{
	return ((b & c) | (~b & d));
}

uint32_t	md5_g(const uint32_t b, const uint32_t c, const uint32_t d)
{
	return ((d & b) | (~d & c));
}

uint32_t	md5_h(const uint32_t b, const uint32_t c, const uint32_t d)
{
	return (b ^ c ^ d);
}

uint32_t	md5_i(const uint32_t b, const uint32_t c, const uint32_t d)
{
	return (c ^ (b | ~d));
}
