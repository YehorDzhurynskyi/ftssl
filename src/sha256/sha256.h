/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
#define SHA256_H

# include "buffer.h"

# define SHA256_PAYLOAD_BIT_SIZE (448)
# define SHA256_LEN_BIT_SIZE (64)
# define SHA256_BLOCK_BIT_SIZE (SHA256_PAYLOAD_BIT_SIZE + SHA256_LEN_BIT_SIZE)
# define SHA256_BLOCK_SIZE (SHA256_BLOCK_BIT_SIZE / CHAR_BIT)

void    sha256_process(struct s_buffer *buffer);

#endif
