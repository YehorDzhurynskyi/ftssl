/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA512_H
#define SHA512_H

# include "buffer.h"

# define SHA512_PAYLOAD_BIT_SIZE (896)
# define SHA512_LEN_BIT_SIZE (128)
# define SHA512_BLOCK_BIT_SIZE (SHA512_PAYLOAD_BIT_SIZE + SHA512_LEN_BIT_SIZE)
# define SHA512_BLOCK_SIZE (SHA512_BLOCK_BIT_SIZE / CHAR_BIT)

void    sha512_process(struct s_buffer *buffer);

#endif
