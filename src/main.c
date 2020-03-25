/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include "request.h"
#include "command.h"
#include "error.h"
#include "md5/md5.h"
#include "sha256/sha256.h"
#include "sha224/sha224.h"
#include "sha512/sha512.h"

void	atexit_callback()
{
	// TODO: remove on release
	// ft_printf("$\n\n\n\n\n");
	// system("leaks ft_ssl");
}

static t_command	*cmd_of(const char *str)
{
    static t_command commands[] = {
        {
            .lname = "md5",
            .uname = "MD5",
            .process_func = md5_process,
            .multiplier = MD5_BLOCK_SIZE
        },
        {
            .lname = "sha256",
            .uname = "SHA256",
            .process_func = sha256_process,
            .multiplier = SHA256_BLOCK_SIZE
        },
        {
            .lname = "sha224",
            .uname = "SHA224",
            .process_func = sha224_process,
            .multiplier = SHA224_BLOCK_SIZE
        },
        {
            .lname = "sha512",
            .uname = "SHA512",
            .process_func = sha512_process,
            .multiplier = SHA512_BLOCK_SIZE
        },
    };

	if (ft_strequ(str, "md5"))
	{
		return (&commands[0]);
	}
    else if (ft_strequ(str, "sha256"))
    {
        return (&commands[1]);
    }
    else if (ft_strequ(str, "sha224"))
    {
        return (&commands[2]);
    }
    else if (ft_strequ(str, "sha512"))
    {
        return (&commands[3]);
    }
	return (NULL);
}

// TODO: remove
void	provide(const t_command *cmd, const t_request *request);

// TODO: -p turns on reading from stdin
// TODO: *stdin of -r (openssl md5 -r)
// TODO: parse commands from STDIN
int						main(const int argc, const char **argv)
{
    t_command   *cmd;
	t_request	request;

	atexit(atexit_callback);
	if (argc < 2 || ((cmd = cmd_of(argv[1])) == NULL))
	{
		if (argc >= 2) // TODO: process stdin instead
		{
			error_invalid_command(argv[1]); // TODO: figure out proper message here on both conditions
		}
		exit(EXIT_FAILURE);
	}
	request = request_parse(argc - 2, argv + 2);
	provide(cmd, &request);
	return (EXIT_SUCCESS);
}
