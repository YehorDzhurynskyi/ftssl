/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_provider.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include "md5_internal.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

static void	md5_verbose_prefix(const struct s_md5 *md5,
char* out, const char* caption, const size_t size, const t_bool use_quotes)
{
	if (!md5->quiet_mode && !md5->reverse_format)
	{
		ft_strcat(out, "MD5 (");
		if (use_quotes)
		{
			ft_strcat(out, "\"");
		}
		ft_strncat(out, (const char*)caption, size);
		if (use_quotes)
		{
			ft_strcat(out, "\"");
		}
		ft_strcat(out, ") = ");
	}
}

static void	md5_verbose_suffix(const struct s_md5 *md5,
char* out, const char* caption, const size_t size, const t_bool use_quotes)
{
	if (!md5->quiet_mode && md5->reverse_format)
	{
		ft_strcat(out, " ");
		if (use_quotes)
		{
			ft_strcat(out, "\"");
		}
		ft_strncat(out, (const char*)caption, size);
		if (use_quotes)
		{
			ft_strcat(out, "\"");
		}
	}
}

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

static void		md5_process_memory(const struct s_md5 *md5,
const t_byte* in, const size_t size)
{
	struct s_buffer	buffer;
	char			*outbuff;
	size_t			outlen;

	outlen = MD5_OUTPUT_SIZE;
	if (!md5->quiet_mode)
	{
		outlen += (md5->reverse_format ? size : size + 11) + 3;
	}
	outbuff = ft_memalloc(sizeof(char) * (outlen + 1));
	md5_verbose_prefix(md5, outbuff, (const char*)in, size, TRUE);
	buffer = buffer_create(MD5_BLOCK_SIZE);
	buffer_append(&buffer, in, size);
	md5_digest(&buffer, ft_strchr(outbuff, '\0'));
	md5_verbose_suffix(md5, outbuff, (const char*)in, size, TRUE);
	ft_putendl_fd(outbuff, STDOUT_FILENO);
	buffer_free(&buffer);
	free(outbuff);
}

void			md5_process(const t_request *request)
{
	const char	*filename;
	int			i;
	int			fd;

	if (request->print_stdin || (request->file_count == 0 && request->input_string == NULL))
	{
		md5_process_stdin(&md5);
	}
	if (md5.input_string != NULL)
	{
		md5_process_memory(&md5, md5.input_string, ft_strlen((char*)md5.input_string));
	}
	i = 0;
	while (i < md5.file_count)
	{
		filename = md5.file_names[i++];
		fd = open(filename, O_RDONLY);
		if (fd < 0)
		{
			md5_perror(filename);
			continue;
		}
		md5_process_file(&md5, fd, filename);
		close(fd);
	}
}
