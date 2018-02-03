/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 15:58:07 by skavunen          #+#    #+#             */
/*   Updated: 2017/04/28 15:30:18 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ls_files(t_list *files, t_als *arg, char *path)
{
	t_item		*inf;
	int			a;
	t_list		*node;

	inf = (t_item*)malloc(sizeof(t_item) * ft_lstlen(files));
	a = 0;
	node = files;
	while (node)
	{
		ft_create_item(&inf[a], node->content, path);
		a++;
		node = node->next;
	}
	if ((arg->l == 1 || arg->n == 1 || arg->o == 1) && path)
		ft_display_total(inf, a);
	ft_display_file(inf, arg, a);
}

void			ls_dirs(t_list *dirs, t_als *arg, int flag, char *path)
{
	t_item		*inf;
	int			a;
	t_list		*node;

	inf = (t_item*)malloc(sizeof(t_item) * ft_lstlen(dirs));
	a = 0;
	node = dirs;
	while (node)
	{
		ft_create_item(&inf[a], node->content, path);
		node = node->next;
		a++;
	}
	ft_lst_free(&dirs);
	arg->d == 1 ? ft_display_file(inf, arg, a) :
					ft_display_dir(inf, arg, a, flag);
}

void			ft_ls(t_als *arg, t_list *list, int flag)
{
	t_list		*files;
	t_list		*dirs;
	DIR			*dir;

	files = NULL;
	dirs = NULL;
	while (list)
	{
		if ((dir = opendir(list->content)) == NULL && ++flag)
			if (errno == ENOTDIR)
				ft_lstpushback(&files, list->content,
					ft_strlen(list->content) + 1);
			else
				ft_error(list->content);
		else
			ft_lstpushback(&dirs, list->content, ft_strlen(list->content) + 1);
		list = list->next;
	}
	if (files && ++flag)
		ls_files(files, arg, NULL);
	if (files && dirs)
		ft_putchar('\n');
	if (dirs)
		ls_dirs(dirs, arg, flag, NULL);
}
