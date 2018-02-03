/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 13:27:20 by skavunen          #+#    #+#             */
/*   Updated: 2017/04/27 14:49:28 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_create_item(t_item *inf, char *name, char *path)
{
	char		*tmp;

	inf->fi = (struct stat*)malloc(sizeof(struct stat));
	inf->name = ft_strdup(name);
	tmp = ft_strjoin(path, name);
	if (!tmp)
		tmp = ft_strdup(name);
	if (path)
		inf->path = ft_strdup(path);
	else
		inf->path = NULL;
	lstat(tmp, inf->fi);
	inf->mor = (S_ISBLK(inf->fi->st_mode) || S_ISCHR(inf->fi->st_mode) ? 1 : 0);
	free(tmp);
}

void			ft_item_del(t_item *inf, int len)
{
	int			a;

	a = 0;
	if (inf)
	{
		while (a < len)
		{
			if (inf[a].path)
				ft_strdel(&inf[a].path);
			free(inf[a].fi);
			ft_strdel(&inf[a].name);
			a++;
		}
		free(inf);
		inf = NULL;
	}
}

char			*ft_path(t_item *inf, int len, int flag, int i)
{
	char		*open;
	char		*buf;
	int			sln;

	open = (inf[i].path != NULL ? ft_strjoin(inf[i].path, inf[i].name) :
			ft_strdup(inf[i].name));
	if (len != 1 || flag > 0)
		ft_printf("%s:\n", open);
	sln = ft_strlen(open);
	if (open[sln - 1] != '/')
	{
		buf = open;
		open = ft_strjoin(open, "/");
		free(buf);
	}
	return (open);
}

int				ft_get_attr(t_item *inf, int len)
{
	int			xaatr;
	int			a;
	int			flag;
	char		*file;

	a = 0;
	xaatr = 0;
	flag = 0;
	while (a < len)
	{
		file = (inf[a].path != NULL ? ft_strjoin(inf[a].path, inf[a].name)
				: ft_strdup(inf[a].name));
		xaatr = listxattr(file, NULL, 0, XATTR_NOFOLLOW);
		if (xaatr > 0)
		{
			inf[a].x = 1;
			flag = 1;
		}
		ft_strdel(&file);
		a++;
	}
	return (flag);
}

int				ft_nlink(t_item *inf, int len)
{
	int			a;
	int			ret;

	a = 0;
	ret = 0;
	while (a < len)
	{
		if (inf[a].fi->st_nlink > 9)
			ret = 1;
		a++;
	}
	return (ret);
}
