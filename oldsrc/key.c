/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key.h"

static t_bool	check_hex(const char *key)
{
	while (*key && ft_ishex(*key))
		key++;
	return (!*key);
}

t_bool			parse_hex(const char *key, unsigned long long *dest)
{
	char	keybuff[MAX_KEY64_LEN];
	size_t	klen;
	int		v;

	if (!check_hex(key))
		return (FALSE);
	*dest = 0;
	ft_memset(keybuff, '0', MAX_KEY64_LEN);
	klen = ft_strlen(key);
	klen = klen > MAX_KEY64_LEN ? MAX_KEY64_LEN : klen;
	ft_memcpy(keybuff, key, klen);
	key = keybuff;
	klen = MAX_KEY64_LEN;
	while (klen--)
	{
		if (ft_isdigit(*key))
			v = *key - '0';
		else if (*key >= 'a' && *key <= 'f')
			v = *key - 'a' + 10;
		else if (*key >= 'A' && *key <= 'F')
			v = *key - 'A' + 10;
		*dest = *dest * 16 + v;
		key++;
	}
	return (TRUE);
}
