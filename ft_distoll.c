/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_distoll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:08:51 by skavunen          #+#    #+#             */
/*   Updated: 2017/04/27 13:16:07 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_find_mor(t_item *inf, int len)
{
	int		a;

	a = 0;
	while (a < len)
	{
		if (inf[a].mor == 1)
			return (1);
		a++;
	}
	return (0);
}

void		ft_print_mode(t_item inf)
{
	if (S_ISDIR(inf.fi->st_mode))
		ft_putchar('d');
	else if (S_ISCHR(inf.fi->st_mode))
		ft_putchar('c');
	else if (S_ISSOCK(inf.fi->st_mode))
		ft_putchar('s');
	else if (S_ISFIFO(inf.fi->st_mode))
		ft_putchar('p');
	else if (S_ISBLK(inf.fi->st_mode))
		ft_putchar('b');
	else if (S_ISLNK(inf.fi->st_mode))
		ft_putchar('l');
	else
		ft_putchar('-');
}

int			ft_find_min(t_item *inf, int len, int flag)
{
	long	res;
	int		a;
	long	tmp;

	a = 0;
	res = 0;
	tmp = 0;
	while (a < len)
	{
		tmp = (flag == 1 ? minor(inf[a].fi->st_rdev)
				: major(inf[a].fi->st_rdev));
		if (tmp > res)
			res = tmp;
		a++;
	}
	a = 0;
	while (res != 0)
	{
		a++;
		res = res / 10;
	}
	return (a);
}

void		ft_print_size(t_item inf, t_view *view)
{
	int		size;

	size = (view->globm == 1 ? 6 : 2);
	if (inf.mor == 1)
	{
		ft_printf("   %*d,", view->major, major(inf.fi->st_rdev));
		ft_printf("%*d ", (view->minor > view->mxsize ? view->minor + 1
		: view->mxsize), minor(inf.fi->st_rdev));
	}
	else
		ft_printf("%*lld ", view->mxsize + size, inf.fi->st_size);
}
