/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 17:34:41 by skavunen          #+#    #+#             */
/*   Updated: 2017/04/27 16:50:56 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					ft_usernum(t_item *inf, int len)
{
	int				a;
	unsigned int	num;

	a = 0;
	num = 0;
	while (a < len)
	{
		if (inf[a].fi->st_uid > num)
			num = inf[a].fi->st_uid;
		a++;
	}
	a = 0;
	while (num != 0)
	{
		a++;
		num = num / 10;
	}
	return (a);
}

int					ft_groupnum(t_item *inf, int len)
{
	int				a;
	unsigned int	res;

	a = 0;
	res = 0;
	while (a < len)
	{
		if (inf[a].fi->st_gid > res)
			res = inf[a].fi->st_gid;
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

int					ft_userchar(t_item *inf, int len)
{
	int				a;
	int				res;
	int				tmp;
	struct passwd	*user;

	a = 0;
	res = 0;
	while (a < len)
	{
		user = getpwuid(inf[a].fi->st_uid);
		tmp = ft_strlen(user->pw_name);
		if (res < (int)tmp)
			res = (int)tmp;
		a++;
	}
	return (res);
}

int					ft_groupchar(t_item *inf, int len)
{
	int				a;
	int				res;
	int				tmp;
	struct group	*grp;

	a = 0;
	res = 0;
	while (a < len)
	{
		grp = getgrgid(inf[a].fi->st_gid);
		tmp = ft_strlen(grp->gr_name);
		if (res < (int)tmp)
			res = (int)tmp;
		a++;
	}
	return (res);
}

t_view				*ft_makeview(t_item *inf, t_als *arg, int len)
{
	t_view			*view;

	view = (t_view*)malloc(sizeof(t_view));
	view->xattr = ft_get_attr(inf, len);
	view->lnk = ft_nlink(inf, len);
	view->mxsize = ft_max_size(inf, len);
	view->user = (arg->n == 1 ? ft_usernum(inf, len) : ft_userchar(inf, len));
	view->group = (arg->n == 1 ? ft_groupnum(inf, len)
					: ft_groupchar(inf, len));
	view->minor = ft_find_min(inf, len, 1);
	view->major = ft_find_min(inf, len, 0);
	view->globm = ft_find_mor(inf, len);
	return (view);
}
