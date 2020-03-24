/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA224_H
#define SHA224_H

# include "buffer.h"

# define SHA224_PAYLOAD_BIT_SIZE (448)
# define SHA224_LEN_BIT_SIZE (64)
# define SHA224_BLOCK_BIT_SIZE (SHA224_PAYLOAD_BIT_SIZE + SHA224_LEN_BIT_SIZE)
# define SHA224_BLOCK_SIZE (SHA224_BLOCK_BIT_SIZE / CHAR_BIT)

void    sha224_process(struct s_buffer *buffer);

#endif
