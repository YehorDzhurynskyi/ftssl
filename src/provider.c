/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   provider.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "request.h"
#include "md5/md5.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

static t_cmd_process_func	g_commands[] = {
	md5_process
};

static t_bool	provide_fd(enum e_cmd_name cmd, int fd)
{
	t_byte	buff[4096];
	ssize_t	ret;

	while ((ret = read(fd, buff, sizeof(buff))) > 0)
	{
		g_commands[cmd](buff, ret);
	}
	return (!ret);
}

static const char *cmd_to_str(enum e_cmd_name cmd)
{
	if (cmd == cmd_name_md5)
	{
		return ("md5");
	}
	return ("");
}

void			provide(const t_request *request, enum e_cmd_name cmd)
{
	const char	*filename;
	int			i;
	int			fd;

	if (request->print_stdin || (!request->nfiles && !request->input_string))
	{
		provide_fd(cmd, STDIN_FILENO);
	}
	if (request->input_string != NULL)
	{
		if (!request->quiet_mode && !request->reverse_format)
		{
			ft_printf("MD5 (\"%s\") = ", request->input_string);
		}
		g_commands[cmd](request->input_string, ft_strlen((char*)request->input_string));
		if (!request->quiet_mode && request->reverse_format)
		{
			ft_printf(" \"%s\"", request->input_string);
		}
		ft_printf("\n");
	}
	i = 0;
	while (i < request->nfiles)
	{
		filename = request->files[i++];
		fd = open(filename, O_RDONLY);
		if (fd < 0)
		{
			ft_printf_fd(STDERR_FILENO, "%s: ", cmd_to_str(cmd));
			perror(filename);
			continue;
		}
		if (!request->quiet_mode && !request->reverse_format)
		{
			ft_printf("MD5 (%s) = ", filename);
		}
		if (!provide_fd(cmd, fd))
		{
			ft_printf_fd(STDERR_FILENO, "%s: ", cmd_to_str(cmd));
			perror(filename);
		}
		else if (!request->quiet_mode && request->reverse_format)
		{
			ft_printf(" %s", filename);
		}
		ft_printf("\n");
		close(fd);
	}
}
