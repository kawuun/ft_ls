/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 13:13:42 by skavunen          #+#    #+#             */
/*   Updated: 2017/04/27 16:56:09 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				ft_dir_to_list(char *open, t_list **file,
									t_als *arg, char *name)
{
	struct dirent	*dir;
	DIR				*d;

	d = opendir(open);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (dir->d_name[0] == '.')
				arg->a == 1 || arg->f == 1 ? ft_lstpushback(file,
				dir->d_name, ft_strlen(dir->d_name) + 1) : NULL;
			else
				ft_lstpushback(file, dir->d_name, ft_strlen(dir->d_name) + 1);
		}
		closedir(d);
	}
	else
		ft_error_perm(name);
}

void				ft_filter(t_item *inf, t_als *arg, int len)
{
	if (arg->t == 1 && arg->f != 1)
	{
		ft_sort(inf, len, arg);
		arg->r == 1 ? ft_sort_rev(inf, len) : NULL;
	}
	else if (arg->f != 1)
	{
		ft_sort_name(inf, len);
		arg->r == 1 ? ft_sort_rev(inf, len) : NULL;
	}
}

void				ft_display_dir(t_item *inf, t_als *arg, int len, int flag)
{
	int				i;
	t_list			*file;
	char			*open;

	i = -1;
	file = NULL;
	ft_filter(inf, arg, len);
	while (++i < len)
	{
		open = ft_path(inf, len, flag, i);
		ft_dir_to_list(open, &file, arg, inf[i].name);
		if (file)
		{
			ls_files(file, arg, open);
			arg->br == 1 ? NULL : ft_lst_free(&file);
		}
		if (file && arg->br == 1)
		{
			ft_recursion_ls(file, arg, open);
			ft_lst_free(&file);
		}
		i + 1 < len ? ft_putchar('\n') : NULL;
		ft_strdel(&open);
	}
	ft_item_del(inf, len);
}

void				ft_display_hard(t_item inf, t_als *arg, t_view *view)
{
	int				i;
	struct passwd	*user;
	struct group	*grp;

	i = 0;
	user = getpwuid(inf.fi->st_uid);
	grp = getgrgid(inf.fi->st_gid);
	ft_print_rights(inf);
	if (inf.x == 1)
	{
		ft_printf("@");
		i++;
	}
	ft_printf("%*d", (view->lnk == 1 ? 4 - i : 3 - i), inf.fi->st_nlink);
	arg->n == 1 ? ft_printf(" %-*d", view->user, inf.fi->st_uid) :
		ft_printf(" %-*s", view->user, user->pw_name);
	if (arg->o == 0)
		arg->n == 1 ? ft_printf("  %-*d", view->group, inf.fi->st_gid) :
			ft_printf("  %-*s", view->group, grp->gr_name);
	view->mxsize += (view->mxsize == 0 ? 1 : 0);
	ft_print_size(inf, view);
	ft_time(inf, arg);
	ft_printf("%s", inf.name);
	ft_link(inf) == 0 ? (void)ft_printf("\n") : NULL;
}

void				ft_display_file(t_item *inf, t_als *arg, int len)
{
	int				i;
	t_view			*view;

	i = 0;
	view = ft_makeview(inf, arg, len);
	ft_filter(inf, arg, len);
	if (arg->l == 1 || arg->n == 1 || arg->o == 1)
		while (i < len)
		{
			ft_display_hard(inf[i], arg, view);
			i++;
		}
	else
		while (i < len)
		{
			ft_printf("%s\n", inf[i].name);
			i++;
		}
	ft_item_del(inf, len);
	free(view);
}
