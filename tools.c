/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 13:05:23 by skavunen          #+#    #+#             */
/*   Updated: 2017/04/26 18:11:40 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_print_rights(t_item inf)
{
	ft_print_mode(inf);
	ft_printf((inf.fi->st_mode & S_IRUSR) ? "r" : "-");
	ft_printf((inf.fi->st_mode & S_IWUSR) ? "w" : "-");
	ft_printf((inf.fi->st_mode & S_IXUSR) ? "x" : "-");
	ft_printf((inf.fi->st_mode & S_IRGRP) ? "r" : "-");
	ft_printf((inf.fi->st_mode & S_IWGRP) ? "w" : "-");
	ft_printf((inf.fi->st_mode & S_IXGRP) ? "x" : "-");
	ft_printf((inf.fi->st_mode & S_IROTH) ? "r" : "-");
	ft_printf((inf.fi->st_mode & S_IWOTH) ? "w" : "-");
	ft_printf((inf.fi->st_mode & S_IXOTH) ? "x" : "-");
}

int				ft_max_size(t_item *inf, int len)
{
	int			a;
	long long	res;

	a = 0;
	res = 0;
	while (a < len)
	{
		if (inf[a].fi->st_size > res)
			res = inf[a].fi->st_size;
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

void			ft_display_total(t_item *inf, int len)
{
	int			a;
	long long	sum;

	a = 0;
	sum = 0;
	while (a < len)
	{
		sum += inf[a].fi->st_blocks;
		a++;
	}
	ft_printf("total %lld\n", sum);
}

int				ft_lstlen(t_list *lst)
{
	t_list		*node;
	int			count;

	node = lst;
	count = 0;
	while (node)
	{
		count++;
		node = node->next;
	}
	return (count);
}

void			ft_lst_free(t_list **lst)
{
	t_list		*node;
	t_list		*buf;

	node = *lst;
	if (node)
	{
		while (node)
		{
			buf = node->next;
			ft_memdel(&node->content);
			free(node);
			node = buf;
		}
		*lst = NULL;
	}
}
