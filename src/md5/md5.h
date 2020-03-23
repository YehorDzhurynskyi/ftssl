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

#ifndef MD5_H
# define MD5_H

# include "buffer.h"
# include "request.h"
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <limits.h>

# define MD5_PAYLOAD_BIT_SIZE (448)
# define MD5_LEN_BIT_SIZE (64)
# define MD5_BLOCK_BIT_SIZE (MD5_PAYLOAD_BIT_SIZE + MD5_LEN_BIT_SIZE)
# define MD5_BLOCK_SIZE (MD5_BLOCK_BIT_SIZE / CHAR_BIT)

void	md5_process(struct s_buffer *buffer);

#endif
