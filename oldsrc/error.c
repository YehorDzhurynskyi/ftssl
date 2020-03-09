/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "ft.h"
#include <stdio.h>
#include <stdlib.h>

extern const char	*g_sslexe_name;

void	print_usage(void)
{
	ft_putstr_fd("usage: ", 2);
	ft_putstr_fd(g_sslexe_name, 2);
	ft_putendl_fd(" command [command opts] [command args]", 2);
	exit(-1);
}

void	print_commands(const char *unknown_command)
{
	ft_putstr_fd(g_sslexe_name, 2);
	ft_putstr_fd(": Error: '", 2);
	ft_putstr_fd(unknown_command, 2);
	ft_putendl_fd("' is invalid command.\n", 2);
	ft_putendl_fd("Standard commands:", 2);
	ft_putendl_fd("", 2);
	ft_putendl_fd("Message digest commands:", 2);
	ft_putendl_fd("", 2);
	ft_putendl_fd("Cipher commands:", 2);
	ft_putendl_fd("base64", 2);
	ft_putendl_fd("des", 2);
	ft_putendl_fd("des-ecb", 2);
	ft_putendl_fd("des-cbc", 2);
	exit(-1);
}

void	print_error(const char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(-1);
}

void	print_errno(const char *msg, const char *msg_arg)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	if (msg_arg)
	{
		ft_putchar_fd('\'', 2);
		ft_putstr_fd(msg_arg, 2);
		ft_putchar_fd('\'', 2);
	}
	if (msg)
		ft_putstr_fd(": ", 2);
	perror(NULL);
	exit(-1);
}

void	print_command_usage(const char *ch, const char *msg,
const t_cipher_info *info)
{
	ft_putstr_fd(info->command_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putendl_fd(ch, 2);
	ft_putstr_fd("usage: ", 2);
	ft_putstr_fd(info->command_name, 2);
	ft_putstr_fd(" ", 2);
	ft_putendl_fd(info->command_usage, 2);
	exit(-1);
}
