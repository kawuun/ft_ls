/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 14:37:08 by skavunen          #+#    #+#             */
/*   Updated: 2017/04/26 18:40:41 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_swap(t_item *i1, t_item *i2)
{
	char		*buf;
	char		*tmp;
	struct stat	*b;
	int			atr;
	int			mr;

	buf = i1->name;
	i1->name = i2->name;
	i2->name = buf;
	tmp = i1->path;
	i1->path = i2->path;
	i2->path = tmp;
	b = i1->fi;
	i1->fi = i2->fi;
	i2->fi = b;
	atr = i1->x;
	i1->x = i2->x;
	i2->x = atr;
	mr = i1->mor;
	i1->mor = i2->mor;
	i2->mor = mr;
}

void			ft_sort_rev(t_item *inf, int len)
{
	int			a;
	int			i;

	a = 0;
	i = len - 1;
	while (a < i)
	{
		ft_swap(&inf[a], &inf[i]);
		a++;
		i--;
	}
}

int				ft_sort_t(t_spec r, t_spec l, t_item *i1, t_item *i2)
{
	if (r.tv_sec < l.tv_sec)
	{
		ft_swap(i1, i2);
		return (1);
	}
	else if (r.tv_sec == l.tv_sec)
	{
		if (r.tv_nsec < l.tv_nsec)
		{
			ft_swap(i1, i2);
			return (1);
		}
		else if (r.tv_nsec == l.tv_nsec)
		{
			if (ft_strcmp(i1->name, i2->name) > 0)
			{
				ft_swap(i1, i2);
				return (1);
			}
			return (0);
		}
	}
	return (0);
}

void			ft_sort(t_item *inf, int len, t_als *arg)
{
	int			i;
	t_spec		r;
	t_spec		l;

	i = 1;
	while (i < len)
	{
		r = (arg->u == 1 ? inf[i - 1].fi->st_atimespec :
			inf[i - 1].fi->st_mtimespec);
		l = (arg->u == 1 ? inf[i].fi->st_atimespec : inf[i].fi->st_mtimespec);
		if (ft_sort_t(r, l, &inf[i - 1], &inf[i]))
			i = 1;
		else
			i++;
	}
}

void			ft_sort_name(t_item *inf, int len)
{
	int			i;

	i = 1;
	while (i < len)
	{
		if (ft_strcmp(inf[i - 1].name, inf[i].name) > 0)
		{
			ft_swap(&inf[i - 1], &inf[i]);
			i = 1;
		}
		else
			i++;
	}
}
