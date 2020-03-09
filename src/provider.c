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

#if 0

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

#else

#if 0
static void	md5_process_file(const struct s_md5 *md5, const int fd, const char *filename)
{
	struct s_buffer	buffer;
	char			*outbuff;
	size_t			outlen;
	size_t			size;

	buffer = buffer_create(MD5_BLOCK_SIZE);
	if (buffer_read_fd(&buffer, fd) >= 0)
	{
		size = ft_strlen(filename);
		outlen = MD5_OUTPUT_SIZE;
		if (!md5->quiet_mode)
		{
			outlen += (md5->reverse_format ? size : size + 11) + 1;
		}
		outbuff = ft_memalloc(sizeof(char) * (outlen + 1));
		md5_verbose_prefix(md5, outbuff, (const char*)filename, size, FALSE);
		md5_digest(&buffer, ft_strchr(outbuff, '\0'));
		md5_verbose_suffix(md5, outbuff, (const char*)filename, size, FALSE);
		ft_putendl_fd(outbuff, STDOUT_FILENO);
		free(outbuff);
	}
	buffer_free(&buffer);
}

static void	md5_process_stdin(const struct s_md5 *md5)
{
	struct s_buffer	buffer;
	char			outbuff[MD5_OUTPUT_SIZE];

	buffer = buffer_create(MD5_BLOCK_SIZE);
	if (buffer_read_fd(&buffer, STDIN_FILENO) >= 0)
	{
		if (md5->print_stdin)
		{
			write(STDOUT_FILENO, buffer_data(&buffer), buffer.size);
		}
		md5_digest(&buffer, outbuff);
		write(STDOUT_FILENO, outbuff, sizeof(outbuff));
		write(STDOUT_FILENO, "\n", 1);
	}
	buffer_free(&buffer);
}
#endif

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

#endif
