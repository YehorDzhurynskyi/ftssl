/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "sslparser.h"

const char	*g_sslexe_name;

static void	process_command(t_command cmd,
const char *command, int ac, const char **av)
{
	t_cipher	cipher;

	if (cmd == cmd_cipher)
	{
		cipher = parse_cipher(command, ac, av);
		process_cipher(&cipher);
	}
}

int			main(int ac, const char **av)
{
	t_command	cmd;

	g_sslexe_name = av[0];
	if (ac <= 1)
		print_usage();
	cmd = parse_command(av[1]);
	if (cmd == cmd_unknown)
		print_commands(av[1]);
	process_command(cmd, av[1], ac - 2, av + 2);
	return (0);
}
