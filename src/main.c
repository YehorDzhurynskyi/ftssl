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
    };

	if (ft_strequ(str, "md5"))
	{
		return (&commands[0]);
	}
    else if (ft_strequ(str, "sha256"))
    {
        return (&commands[1]);
    }
	return (NULL);
}

const char text[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed facilisis nisi augue, at mollis arcu eleifend sit amet. Phasellus ultrices lobortis orci, ut ullamcorper justo blandit condimentum. In semper ante ut turpis varius hendrerit. Mauris dui nisi, rutrum a leo eget, vehicula fringilla urna. Phasellus sed augue porttitor, laoreet sapien et, ullamcorper mi. Cras a mauris nibh. Proin in ligula quam. Praesent ut tincidunt dui. Fusce nec condimentum arcu. Sed lobortis semper eros, eget ullamcorper sapien venenatis ac. Nam sollicitudin urna et dolor volutpat commodo. Donec imperdiet purus id velit sagittis ullamcorper. Mauris vitae dolor maximus, sollicitudin mauris vitae, porta nunc. Aliquam erat volutpat. Ut vel vulputate magna, id consequat lorem. Duis malesuada, eros ac elementum semper, magna dui tempus ante, euismod vulputate metus eros et nisi. Nullam posuere vehicula finibus. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Phasellus congue ut turpis vitae rhoncus.";

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
	//request.input_string = (t_byte*)text;
	provide(cmd, &request);
	return (EXIT_SUCCESS);
}
