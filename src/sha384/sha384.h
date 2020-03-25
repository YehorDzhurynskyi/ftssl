/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA384_H
#define SHA384_H

# include "buffer.h"

# define SHA384_PAYLOAD_BIT_SIZE (896)
# define SHA384_LEN_BIT_SIZE (128)
# define SHA384_BLOCK_BIT_SIZE (SHA384_PAYLOAD_BIT_SIZE + SHA384_LEN_BIT_SIZE)
# define SHA384_BLOCK_SIZE (SHA384_BLOCK_BIT_SIZE / CHAR_BIT)

void    sha384_process(struct s_buffer *buffer);

#endif
