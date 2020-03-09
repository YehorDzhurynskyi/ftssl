/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cipher_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher.h"
#include "ft.h"
#include <stdlib.h>
#include "error.h"

static int	parse_ed(t_cipher *cipher, char ch)
{
	cipher->mode = ch == 'e' ? cpr_mode_encode : cpr_mode_decode;
	return (1);
}

static int	parse_iob(t_cipher *cipher, const char *nextarg, char ch)
{
	char	**file;

	if (ch == 'b')
		cipher->line_length = ft_atoi(nextarg);
	else
	{
		file = ch == 'i' ? &cipher->input_file : &cipher->output_file;
		free(*file);
		*file = ft_strdup(nextarg);
	}
	return (2);
}

static int	append_option(t_cipher *cipher, int ac,
const char **av, const t_cipher_info *info)
{
	const char	*op;
	int			cipher_ret;

	op = *av + 1;
	cipher_ret = info->append_option != NULL
	? info->append_option(cipher, ac, av, info) : 0;
	if (cipher_ret != 0)
		return (cipher_ret);
	else if (ft_strequ(op, "i")
	|| ft_strequ(op, "o")
	|| ft_strequ(op, "b"))
	{
		if (ac - 1 <= 0)
			print_command_usage(op, "option requires an argument -- ", info);
		return (parse_iob(cipher, *(av + 1), *op));
	}
	else if (ft_strequ(op, "e") || ft_strequ(op, "d"))
		return (parse_ed(cipher, *op));
	else if (ft_strequ(op, "-"))
		return (1);
	print_command_usage(op, "invalid option -- ", info);
	return (-1);
}

void		cipher_parse_options(t_cipher *cipher, int ac,
const char **av, const t_cipher_info *info)
{
	int	option_offset;

	while (ac)
	{
		if (**av != '-')
		{
			free(cipher->input_file);
			cipher->input_file = ft_strdup(*av);
			return ;
		}
		option_offset = append_option(cipher, ac, av, info);
		av += option_offset;
		ac -= option_offset;
	}
}
