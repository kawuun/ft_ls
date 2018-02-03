/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 19:03:46 by skavunen          #+#    #+#             */
/*   Updated: 2017/04/27 13:41:40 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_rec_sec(char *name, t_list **dirs, void *data)
{
	DIR		*d;

	d = opendir(name);
	if (d)
	{
		ft_lstpushback(dirs, data, ft_strlen((char*)data) + 1);
		closedir(d);
	}
	else
	{
		if (errno == EACCES)
			ft_lstpushback(dirs, data, ft_strlen((char*)data) + 1);
	}
}

void		ft_recursion_ls(t_list *file, t_als *arg, char *path)
{
	t_list	*dirs;
	char	*buf;

	dirs = NULL;
	while (file)
	{
		buf = ft_strjoin(path, file->content);
		if (ft_strcmp(file->content, ".") == 0
			|| ft_strcmp(file->content, "..") == 0)
		{
			file = file->next;
		}
		else
		{
			ft_rec_sec(buf, &dirs, file->content);
			file = file->next;
		}
		ft_strdel(&buf);
	}
	if (dirs)
	{
		ft_printf("\n");
		ls_dirs(dirs, arg, 1, path);
	}
	ft_lst_free(&file);
}

int			ft_link(t_item inf)
{
	char	link[100];
	int		r;
	char	*name;

	name = ft_strjoin(inf.path, inf.name);
	if (!name)
		name = ft_strdup(inf.name);
	if (S_ISLNK(inf.fi->st_mode))
	{
		r = readlink(name, link, 100);
		link[r] = '\0';
		ft_printf(" -> %s\n", link);
		ft_strdel(&name);
		return (1);
	}
	ft_strdel(&name);
	return (0);
}

void		ft_time(t_item inf, t_als *arg)
{
	time_t	now;
	time_t	file;
	char	*tmp;
	char	*buf;

	time(&now);
	file = (arg->u == 1 ? inf.fi->st_atime : inf.fi->st_mtime);
	tmp = ctime(&file);
	if ((now - file < 15778476) && (now - file >= 0))
	{
		buf = ft_strsub(tmp, 4, 12);
		ft_printf("%8s ", buf);
		ft_strdel(&buf);
	}
	else
	{
		buf = ft_strsub(tmp, 4, 7);
		ft_printf("%7s", buf);
		ft_strdel(&buf);
		buf = ft_strsub(tmp, 19, 5);
		ft_printf("%5s ", buf);
		ft_strdel(&buf);
	}
}
