/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "request.h"

static t_bool	request_parse_flag(t_request *request, const char *arg)
{
	if (ft_strequ(arg, "-p"))
	{
		request->print_stdin = TRUE;
	}
	else if (ft_strequ(arg, "-q"))
	{
		request->quiet_mode = TRUE;
	}
	else if (ft_strequ(arg, "-r"))
	{
		request->reverse_format = TRUE;
	}
	else
	{
		return (FALSE);
	}
	return (TRUE);
}

t_request		request_parse(const int argc, const char **argv)
{
	t_request	request;
	int			i;

	ft_memset(&request, 0x0, sizeof(t_request));
	i = 0;
	while (i < argc)
	{
		if (!request_parse_flag(&request, argv[i]))
		{
			if (ft_strequ(argv[i], "-s"))
			{
				if (i + 1 < argc)
				{
					request.input_string = (t_byte*)argv[++i];
				}
			}
			else
			{
				break;
			}
		}
		++i;
	}
	request.files = argv + i;
	request.nfiles = argc - i;
	return (request);
}
