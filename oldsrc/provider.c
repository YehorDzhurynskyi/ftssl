/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   provider.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "provider.h"
#include <stdlib.h>
#include <unistd.h>
#include "error.h"

static t_amap	g_restmap = (t_amap){NULL, 0};

static void				clear_providerent(void **ent)
{
	t_providerent	*pent;

	pent = *ent;
	ft_memdel((void**)&pent->restbuff);
	ft_memdel(ent);
}

static t_bool			process_rest(t_cipher *cipher,
t_providerent *ent, t_provider provide, int entkey)
{
	unsigned char	*data;
	size_t			nletter;

	if (!ent->info->size)
	{
		if (ent->rest_size)
			provide(cipher, ent, ent->restbuff, ent->rest_size);
		provide(cipher, ent, NULL, 0);
		amap_remove(&g_restmap, entkey, clear_providerent);
		return (FALSE);
	}
	nletter = ent->info->size + ent->rest_size > ent->info->dim
	? ent->info->dim : ent->info->size + ent->rest_size;
	data = (unsigned char*)malloc(sizeof(unsigned char) * nletter);
	if (!data)
		print_errno(NULL, NULL);
	ft_memcpy(data, ent->restbuff, ent->rest_size);
	ft_memcpy(data + ent->rest_size, ent->info->src, nletter - ent->rest_size);
	provide(cipher, ent, data, nletter);
	free(data);
	ent->info->size = ent->info->size >= nletter - ent->rest_size
	? ent->info->size - nletter + ent->rest_size : 0;
	return (TRUE);
}

static t_providerent	*get_providerent(t_provider_info *info, int entkey)
{
	t_providerent	*ent;

	ent = amap_contains(&g_restmap, entkey)
	? amap_get(&g_restmap, entkey) : NULL;
	if (!ent)
	{
		ent = (t_providerent*)malloc(sizeof(t_providerent));
		if (!ent)
			print_errno(NULL, NULL);
		ent->restbuff = malloc(sizeof(unsigned char) * info->dim);
		if (!ent->restbuff)
			print_errno(NULL, NULL);
		ent->rest_size = 0;
		ent->linecount = 0;
		amap_put(&g_restmap, entkey, ent);
	}
	return (ent);
}

static size_t			prepare_decoding(t_cipher *cipher, t_providerent *ent)
{
	unsigned char	*src;
	int				shift;
	int				i;

	if (cipher->line_length == 0)
		return (ent->info->size);
	src = (unsigned char*)ent->info->src;
	shift = ent->linecount % cipher->line_length;
	shift = *src == '\n' && shift == 0 ? 0
	: cipher->line_length - shift - ent->rest_size;
	if (shift < 0)
		shift = -shift;
	i = 0;
	while (shift < (int)ent->info->size - i)
	{
		ft_memmove(src + shift, src + shift + 1, ent->info->size - ++i - shift);
		shift += cipher->line_length;
	}
	return (ent->info->size - i);
}

int						provide_input(t_cipher *cipher,
t_provider_info *info, t_provider provide)
{
	unsigned		i;
	int				entkey;
	t_providerent	*ent;

	entkey = ((info->redirection_count & ((1U << 16) - 1)) << 16)
	| (info->fd & ((1U << 16) - 1));
	if (g_restmap.items == NULL)
		amap_init(&g_restmap, 3);
	ent = get_providerent(info, entkey);
	ent->info = info;
	if (cipher->mode == cpr_mode_decode)
		info->size = prepare_decoding(cipher, ent);
	if (!process_rest(cipher, ent, provide, entkey))
		return (0);
	i = 0;
	while (info->size >= info->dim)
	{
		provide(cipher, ent, info->src + info->dim
		- ent->rest_size + i++ * info->dim, info->dim);
		info->size -= info->dim;
	}
	ft_memcpy(ent->restbuff, info->src + info->dim
	- ent->rest_size + i * info->dim, info->size);
	ent->rest_size = info->size;
	return (ent->linecount);
}
