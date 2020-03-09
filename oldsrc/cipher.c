/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cipher.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "ft.h"
#include "error.h"

#define BSIZE	256

static void	process_data(t_action act, t_cipher *cipher, int in_fd, int out_fd)
{
	unsigned char	buff[BSIZE + 1];
	ssize_t			ret;

	while ((ret = read(in_fd, buff, BSIZE)) > 0)
		act(cipher, out_fd, buff, ret);
	if (ret < 0)
		print_errno(NULL, NULL);
	act(cipher, out_fd, buff, 0);
}

static void	cleanup_cipher(t_cipher *cipher)
{
	free(cipher->input_file);
	free(cipher->output_file);
	free(cipher->extra);
}

void		process_cipher(t_cipher *cipher)
{
	int			in_fd;
	int			out_fd;
	t_action	act;

	in_fd = cipher->input_file == NULL || ft_strequ(cipher->input_file, "-")
	? STDIN_FILENO : open(cipher->input_file, O_RDONLY);
	out_fd = cipher->output_file == NULL || ft_strequ(cipher->output_file, "-")
	? STDOUT_FILENO : open(cipher->output_file,
	O_WRONLY | O_CREAT | O_TRUNC, 0xffffffff);
	if (in_fd < 0)
		print_errno("Unable to open ", cipher->input_file);
	if (out_fd < 0)
		print_errno("Unable to create ", cipher->output_file);
	act = cipher->mode == cpr_mode_encode ? cipher->encode : cipher->decode;
	process_data(act, cipher, in_fd, out_fd);
	close(in_fd);
	close(out_fd);
	cleanup_cipher(cipher);
}
