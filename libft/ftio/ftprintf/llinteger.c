/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llinteger.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:49:36 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/26 14:39:46 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "number_manager.h"

extern va_list	g_ftprintf_args;

void	print_llinteger(t_conversion *c)
{
	unsigned long long	n;
	int					is_neg;

	is_neg = 0;
	if (c->type == type_d || c->type == type_i)
	{
		n = (long long)va_arg(g_ftprintf_args, long long);
		if ((long long)n < 0)
		{
			is_neg = 1;
			n = ~n + 1;
		}
	}
	else
		n = (unsigned long long)va_arg(g_ftprintf_args, unsigned long long);
	print_inumber(n, is_neg, c);
}
