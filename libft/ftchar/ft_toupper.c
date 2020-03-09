/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 17:57:41 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/27 14:42:36 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_toupper(int c)
{
	int	sub;

	sub = 'a' - 'A';
	if (c >= 'a' && c <= 'z')
		c -= sub;
	return (c);
}
