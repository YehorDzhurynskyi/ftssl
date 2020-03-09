/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sslparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sslparser.h"
#include "ft.h"
#include "b64.h"
#include "des.h"

t_command				parse_command(const char *command)
{
	if (ft_strequ(command, "base64") || ft_strequ(command, "des")
	|| ft_strequ(command, "des-ecb") || ft_strequ(command, "des-cbc"))
		return (cmd_cipher);
	return (cmd_unknown);
}

static t_cipher_info	get_des_cipher_info(const char *command)
{
	t_cipher_info	info;

	info.parse_options = des_parse_options;
	info.append_option = des_append_option;
	if (ft_strequ(command, "des-cbc"))
		info.command_usage = "[-a] [-b line_length] [-k hex_key] "
		"[-v hex_initial_vector] [-d | -e] [-i in_file] [-o out_file]";
	else
		info.command_usage = "[-a] [-b line_length] [-k hex_key]"
		" [-d | -e] [-i in_file] [-o out_file]";
	return (info);
}

t_cipher				parse_cipher(const char *command,
int ac, const char **av)
{
	t_cipher		cipher;
	t_cipher_info	info;

	info = (t_cipher_info){NULL, NULL, cipher_parse_options, NULL};
	cipher = (t_cipher){0, NULL, NULL, NULL, NULL, NULL, 0};
	if (ft_strequ(command, "base64"))
	{
		info.command_usage = "[-d | -e] [-b line_length]"
		" [-i in_file] [-o out_file]";
		cipher = (t_cipher){0, NULL, NULL, &b64_encode, &b64_decode, NULL, 64};
	}
	else if (ft_strequ(command, "des") || ft_strequ(command, "des-ecb")
	|| ft_strequ(command, "des-cbc"))
	{
		cipher = (t_cipher){0, NULL, NULL, &des_encode, &des_decode, NULL, 64};
		info = get_des_cipher_info(command);
	}
	else
		return (cipher);
	info.command_name = (char*)command;
	info.parse_options(&cipher, ac, av, &info);
	return (cipher);
}
