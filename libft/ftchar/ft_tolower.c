/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 18:00:37 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/27 14:30:55 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_tolower(int c)
{
	int	sub;

	sub = 'a' - 'A';
	if (c >= 'A' && c <= 'Z')
		c += sub;
	return (c);
}
