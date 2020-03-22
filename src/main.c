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
#include "error.h"

void	atexit_callback()
{
	// TODO: remove on release
	// ft_printf("$\n\n\n\n\n");
	// system("leaks ft_ssl");
}

static enum e_cmd_name	cmd_name_of(const char *str)
{
	if (ft_strequ(str, "md5"))
	{
		return (cmd_name_md5);
	}
	return (cmd_name_unknown);
}

// TODO: remove
void	provide(const t_request *request, enum e_cmd_name cmd);

// TODO: -p turns on reading from stdin
// TODO: *stdin of -r (openssl md5 -r)
// TODO: parse commands from STDIN
int						main(const int argc, const char **argv)
{
	enum e_cmd_name	cmd_name;
	t_request		request;

	atexit(atexit_callback);
	if (argc < 2 || ((cmd_name = cmd_name_of(argv[1])) == cmd_name_unknown))
	{
		if (argc >= 2) // TODO: process stdin instead
		{
			error_invalid_command(argv[1]); // TODO: figure out proper message here on both conditions
		}
		exit(EXIT_FAILURE);
	}
	request = request_parse(argc - 2, argv + 2);
	provide(&request, cmd_name);
	return (EXIT_SUCCESS);
}
