/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 15:42:15 by skavunen          #+#    #+#             */
/*   Updated: 2017/04/28 15:33:34 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_error(char *s)
{
	DIR		*dir;

	if ((dir = opendir(s)) == NULL)
	{
		if (errno == ENOENT)
		{
			write(1, "ls: ", 4);
			ft_putstr(s);
			ft_putstr(": No such file or directory\n");
		}
		else
			ft_error_perm(s);
	}
}

void		ft_error_arg(char c)
{
	int		a;

	a = -1;
	write(1, "ft_ls: illegal option -- ", 25);
	ft_putchar(c);
	ft_putchar('\n');
	ft_putstr("usage: ls [-Radflnortu] [file ...]\n");
	exit(EXIT_FAILURE);
}

void		ft_error_perm(char *s)
{
	write(1, "ls: ", 4);
	ft_putstr(s);
	ft_putstr(": Permission denied\n");
}
