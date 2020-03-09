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

t_byte	md5_f(const t_byte a, const t_byte b, const t_byte c)
{
	return (a & b) | (~a & c);
}

t_byte	md5_g(const t_byte a, const t_byte b, const t_byte c)
{
	return (a & c) | (~c & b);
}

t_byte	md5_h(const t_byte a, const t_byte b, const t_byte c)
{
	return a ^ b ^ c;
}

t_byte	md5_i(const t_byte a, const t_byte b, const t_byte c)
{
	return b ^ (~c | a);
}
