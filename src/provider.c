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

static const char			*g_cmd_name_lower[] = {
	"md5"
};

static const char			*g_cmd_name_upper[] = {
	"MD5"
};

static t_cmd_process_func	g_commands[] = {
	md5_process
};

static t_bool	provide_fd(enum e_cmd_name cmd, int fd, t_bool print_in)
{
	struct s_buffer	buffer;
	t_bool			result;

	buffer = buffer_create(MD5_BLOCK_SIZE);
	if ((result = buffer_read_fd(&buffer, fd)))
	{
		if (print_in)
		{
			write(STDOUT_FILENO, buffer_data(&buffer), buffer.size);
		}
		g_commands[cmd](&buffer);
	}
	buffer_free(&buffer);
	return (result);
}

static void		provide_memory(const t_request *request,
								enum e_cmd_name cmd,
								const t_byte *in,
								const size_t size)
{
	struct s_buffer	buffer;

	buffer = buffer_create(MD5_BLOCK_SIZE);
	buffer_append(&buffer, in, size);
	if (!request->quiet_mode && !request->reverse_format)
	{
		ft_printf("%s (\"%s\") = ", g_cmd_name_upper[cmd], in);
	}
	g_commands[cmd](&buffer);
	if (!request->quiet_mode && request->reverse_format)
	{
		ft_printf(" \"%s\"", in);
	}
	ft_printf("\n");
	buffer_free(&buffer);
}

void			provide(const t_request *request, enum e_cmd_name cmd)
{
	const char	*filename;
	int			i;
	int			fd;

	if (request->print_stdin || (!request->nfiles && !request->input_string))
	{
		provide_fd(cmd, STDIN_FILENO, request->print_stdin);
		ft_printf("\n");
	}
	if (request->input_string != NULL)
	{
		provide_memory(request, cmd, request->input_string, ft_strlen((char*)request->input_string));
	}
	i = 0;
	while (i < request->nfiles)
	{
		filename = request->files[i++];
		fd = open(filename, O_RDONLY);
		if (fd < 0)
		{
			ft_printf_fd(STDERR_FILENO, "%s: ", g_cmd_name_lower[cmd]);
			perror(filename);
			continue;
		}
		if (!request->quiet_mode && !request->reverse_format)
		{
			ft_printf("%s (%s) = ", g_cmd_name_upper[cmd], filename);
		}
		if (!provide_fd(cmd, fd, FALSE))
		{
			ft_printf_fd(STDERR_FILENO, "%s: ", g_cmd_name_lower[cmd]);
			perror(filename);
			close(fd);
			continue;
		}
		else if (!request->quiet_mode && request->reverse_format)
		{
			ft_printf(" %s", filename);
		}
		ft_printf("\n");
		close(fd);
	}
}
