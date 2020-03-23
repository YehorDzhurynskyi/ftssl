/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_rounds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h> // TODO: remove
#include "md5/md5_internal.h"

static uint32_t g_T[64] =
{
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,

	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,

	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,

	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

static uint32_t	rotl(const uint32_t v, uint32_t r)
{
	assert(r < 32);
	return ((v << r) | (v >> (32 - r)));
}

void				md5_round1(const uint32_t *x, uint32_t v[4])
{
	v[0] = v[1] + rotl(v[0] + md5_f(v[1], v[2], v[3]) + x[0] + g_T[0], 7);
	v[3] = v[0] + rotl(v[3] + md5_f(v[0], v[1], v[2]) + x[1] + g_T[1], 12);
	v[2] = v[3] + rotl(v[2] + md5_f(v[3], v[0], v[1]) + x[2] + g_T[2], 17);
	v[1] = v[2] + rotl(v[1] + md5_f(v[2], v[3], v[0]) + x[3] + g_T[3], 22);

	v[0] = v[1] + rotl(v[0] + md5_f(v[1], v[2], v[3]) + x[4] + g_T[4], 7);
	v[3] = v[0] + rotl(v[3] + md5_f(v[0], v[1], v[2]) + x[5] + g_T[5], 12);
	v[2] = v[3] + rotl(v[2] + md5_f(v[3], v[0], v[1]) + x[6] + g_T[6], 17);
	v[1] = v[2] + rotl(v[1] + md5_f(v[2], v[3], v[0]) + x[7] + g_T[7], 22);

	v[0] = v[1] + rotl(v[0] + md5_f(v[1], v[2], v[3]) + x[8] + g_T[8], 7);
	v[3] = v[0] + rotl(v[3] + md5_f(v[0], v[1], v[2]) + x[9] + g_T[9], 12);
	v[2] = v[3] + rotl(v[2] + md5_f(v[3], v[0], v[1]) + x[10] + g_T[10], 17);
	v[1] = v[2] + rotl(v[1] + md5_f(v[2], v[3], v[0]) + x[11] + g_T[11], 22);

	v[0] = v[1] + rotl(v[0] + md5_f(v[1], v[2], v[3]) + x[12] + g_T[12], 7);
	v[3] = v[0] + rotl(v[3] + md5_f(v[0], v[1], v[2]) + x[13] + g_T[13], 12);
	v[2] = v[3] + rotl(v[2] + md5_f(v[3], v[0], v[1]) + x[14] + g_T[14], 17);
	v[1] = v[2] + rotl(v[1] + md5_f(v[2], v[3], v[0]) + x[15] + g_T[15], 22);
}

void				md5_round2(const uint32_t *x, uint32_t v[4])
{
	v[0] = v[1] + rotl(v[0] + md5_g(v[1], v[2], v[3]) + x[1] + g_T[16], 5);
	v[3] = v[0] + rotl(v[3] + md5_g(v[0], v[1], v[2]) + x[6] + g_T[17], 9);
	v[2] = v[3] + rotl(v[2] + md5_g(v[3], v[0], v[1]) + x[11] + g_T[18], 14);
	v[1] = v[2] + rotl(v[1] + md5_g(v[2], v[3], v[0]) + x[0] + g_T[19], 20);

	v[0] = v[1] + rotl(v[0] + md5_g(v[1], v[2], v[3]) + x[5] + g_T[20], 5);
	v[3] = v[0] + rotl(v[3] + md5_g(v[0], v[1], v[2]) + x[10] + g_T[21], 9);
	v[2] = v[3] + rotl(v[2] + md5_g(v[3], v[0], v[1]) + x[15] + g_T[22], 14);
	v[1] = v[2] + rotl(v[1] + md5_g(v[2], v[3], v[0]) + x[4] + g_T[23], 20);

	v[0] = v[1] + rotl(v[0] + md5_g(v[1], v[2], v[3]) + x[9] + g_T[24], 5);
	v[3] = v[0] + rotl(v[3] + md5_g(v[0], v[1], v[2]) + x[14] + g_T[25], 9);
	v[2] = v[3] + rotl(v[2] + md5_g(v[3], v[0], v[1]) + x[3] + g_T[26], 14);
	v[1] = v[2] + rotl(v[1] + md5_g(v[2], v[3], v[0]) + x[8] + g_T[27], 20);

	v[0] = v[1] + rotl(v[0] + md5_g(v[1], v[2], v[3]) + x[13] + g_T[28], 5);
	v[3] = v[0] + rotl(v[3] + md5_g(v[0], v[1], v[2]) + x[2] + g_T[29], 9);
	v[2] = v[3] + rotl(v[2] + md5_g(v[3], v[0], v[1]) + x[7] + g_T[30], 14);
	v[1] = v[2] + rotl(v[1] + md5_g(v[2], v[3], v[0]) + x[12] + g_T[31], 20);
}

void				md5_round3(const uint32_t *x, uint32_t v[4])
{
	v[0] = v[1] + rotl(v[0] + md5_h(v[1], v[2], v[3]) + x[5] + g_T[32], 4);
	v[3] = v[0] + rotl(v[3] + md5_h(v[0], v[1], v[2]) + x[8] + g_T[33], 11);
	v[2] = v[3] + rotl(v[2] + md5_h(v[3], v[0], v[1]) + x[11] + g_T[34], 16);
	v[1] = v[2] + rotl(v[1] + md5_h(v[2], v[3], v[0]) + x[14] + g_T[35], 23);

	v[0] = v[1] + rotl(v[0] + md5_h(v[1], v[2], v[3]) + x[1] + g_T[36], 4);
	v[3] = v[0] + rotl(v[3] + md5_h(v[0], v[1], v[2]) + x[4] + g_T[37], 11);
	v[2] = v[3] + rotl(v[2] + md5_h(v[3], v[0], v[1]) + x[7] + g_T[38], 16);
	v[1] = v[2] + rotl(v[1] + md5_h(v[2], v[3], v[0]) + x[10] + g_T[39], 23);

	v[0] = v[1] + rotl(v[0] + md5_h(v[1], v[2], v[3]) + x[13] + g_T[40], 4);
	v[3] = v[0] + rotl(v[3] + md5_h(v[0], v[1], v[2]) + x[0] + g_T[41], 11);
	v[2] = v[3] + rotl(v[2] + md5_h(v[3], v[0], v[1]) + x[3] + g_T[42], 16);
	v[1] = v[2] + rotl(v[1] + md5_h(v[2], v[3], v[0]) + x[6] + g_T[43], 23);

	v[0] = v[1] + rotl(v[0] + md5_h(v[1], v[2], v[3]) + x[9] + g_T[44], 4);
	v[3] = v[0] + rotl(v[3] + md5_h(v[0], v[1], v[2]) + x[12] + g_T[45], 11);
	v[2] = v[3] + rotl(v[2] + md5_h(v[3], v[0], v[1]) + x[15] + g_T[46], 16);
	v[1] = v[2] + rotl(v[1] + md5_h(v[2], v[3], v[0]) + x[2] + g_T[47], 23);
}

void				md5_round4(const uint32_t *x, uint32_t v[4])
{
	v[0] = v[1] + rotl(v[0] + md5_i(v[1], v[2], v[3]) + x[0] + g_T[48], 6);
	v[3] = v[0] + rotl(v[3] + md5_i(v[0], v[1], v[2]) + x[7] + g_T[49], 10);
	v[2] = v[3] + rotl(v[2] + md5_i(v[3], v[0], v[1]) + x[14] + g_T[50], 15);
	v[1] = v[2] + rotl(v[1] + md5_i(v[2], v[3], v[0]) + x[5] + g_T[51], 21);

	v[0] = v[1] + rotl(v[0] + md5_i(v[1], v[2], v[3]) + x[12] + g_T[52], 6);
	v[3] = v[0] + rotl(v[3] + md5_i(v[0], v[1], v[2]) + x[3] + g_T[53], 10);
	v[2] = v[3] + rotl(v[2] + md5_i(v[3], v[0], v[1]) + x[10] + g_T[54], 15);
	v[1] = v[2] + rotl(v[1] + md5_i(v[2], v[3], v[0]) + x[1] + g_T[55], 21);

	v[0] = v[1] + rotl(v[0] + md5_i(v[1], v[2], v[3]) + x[8] + g_T[56], 6);
	v[3] = v[0] + rotl(v[3] + md5_i(v[0], v[1], v[2]) + x[15] + g_T[57], 10);
	v[2] = v[3] + rotl(v[2] + md5_i(v[3], v[0], v[1]) + x[6] + g_T[58], 15);
	v[1] = v[2] + rotl(v[1] + md5_i(v[2], v[3], v[0]) + x[13] + g_T[59], 21);

	v[0] = v[1] + rotl(v[0] + md5_i(v[1], v[2], v[3]) + x[4] + g_T[60], 6);
	v[3] = v[0] + rotl(v[3] + md5_i(v[0], v[1], v[2]) + x[11] + g_T[61], 10);
	v[2] = v[3] + rotl(v[2] + md5_i(v[3], v[0], v[1]) + x[2] + g_T[62], 15);
	v[1] = v[2] + rotl(v[1] + md5_i(v[2], v[3], v[0]) + x[9] + g_T[63], 21);
}
