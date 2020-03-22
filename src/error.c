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
#include <unistd.h>
#include <stdlib.h>

// TODO: finish
static const char g_usage_msg[] =
"usage: ft_ssl command [command opts] [command args]\n";
static const char g_invalid_cmd_prefix_msg[] =
"ft_ssl: Error: '";
static const char g_invalid_cmd_suffix_msg[] =
"' is an invalid command.\n\n";
static const char g_standard_cmds_msg[] =
"Standard commands:\n\n";
static const char g_digest_cmds_msg[] =
"Message Digest commands:\n"
"md5\n"
"sha224\n"
"sha256\n"
"sha384\n"
"sha512\n"
"\n";
static const char g_cipher_cmds_msg[] =
"Cipher commands:\n";

static const size_t g_cmd_msg_len =
sizeof(g_invalid_cmd_prefix_msg) - 1 +
sizeof(g_invalid_cmd_suffix_msg) - 1 +
sizeof(g_standard_cmds_msg) - 1 +
sizeof(g_digest_cmds_msg) - 1 +
sizeof(g_cipher_cmds_msg) - 1;

void error_perror(const char *prefix)
{
	ft_putstr_fd(prefix, STDERR_FILENO);
	perror(NULL);
}

void error_invalid_command(const char *cmd_name)
{
	char	*error_msg_buf;
	size_t	error_msg_len;

	error_msg_len = g_cmd_msg_len + ft_strlen(cmd_name) + 1;
	error_msg_buf = malloc(sizeof(char) * error_msg_len);
	*error_msg_buf = '\0';
	ft_strcat(error_msg_buf, g_invalid_cmd_prefix_msg);
	ft_strcat(error_msg_buf, cmd_name);
	ft_strcat(error_msg_buf, g_invalid_cmd_suffix_msg);
	ft_strcat(error_msg_buf, g_standard_cmds_msg);
	ft_strcat(error_msg_buf, g_digest_cmds_msg);
	ft_strcat(error_msg_buf, g_cipher_cmds_msg);
	write(STDERR_FILENO, error_msg_buf, error_msg_len - 1);
	free(error_msg_buf);
}

void error_usage(void)
{
	ft_putstr_fd(g_usage_msg, STDERR_FILENO);
}
