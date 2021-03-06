/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/07 17:52:19 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_H
# define REQUEST_H

# include "ft.h"
# include "buffer.h"

typedef struct
{
	t_bool		print_stdin;
	t_bool		quiet_mode;
	t_bool		reverse_format;
	t_byte		*input_string;
	const char	**files;
	int			nfiles;
}	t_request;

t_request	request_parse(const int argc, const char **argv);

#endif
