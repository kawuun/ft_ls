/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 14:38:02 by skavunen          #+#    #+#             */
/*   Updated: 2017/04/27 13:03:35 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H

# define FT_LS_H
# include <stdio.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include "libft/libft.h"
# include <errno.h>
# include <sys/xattr.h>

typedef struct timespec	t_spec;

typedef struct	s_als
{
	int		a;
	int		r;
	int		l;
	int		n;
	int		t;
	int		d;
	int		f;
	int		u;
	int		o;
	int		br;

}				t_als;

typedef struct	s_view
{
	int		xattr;
	int		mxsize;
	int		lnk;
	int		user;
	int		group;
	int		minor;
	int		major;
	int		globm;
}				t_view;

typedef struct	s_item
{
	struct stat	*fi;
	char		*path;
	char		*name;
	int			x;
	int			mor;
}				t_item;

void			ft_get_params(int nb, char **s, t_als *arg, t_list *list);
void			ft_setflag(t_als *arg, char *s);
int				ft_checkflag(char *s);
t_als			*ft_newarg(void);
void			ft_ls(t_als *arg, t_list *list, int flag);
void			ft_error_arg(char c);
void			ft_error(char *s);
void			ft_display_file(t_item *inf, t_als *arg, int len);
int				ft_lstlen(t_list *lst);
void			ft_swap(t_item *i1, t_item *i2);
void			ft_sort(t_item *inf, int len, t_als *arg);
void			ft_display_file(t_item *inf, t_als *arg, int len);
void			ft_filter(t_item *inf, t_als *arg, int len);
void			ft_sort_name(t_item *inf, int len);
void			ft_display_dir(t_item *inf, t_als *arg, int len, int flag);
void			ls_files(t_list *files, t_als *arg, char *path);
void			ft_lst_free(t_list **lst);
void			ft_create_item(t_item *inf, char *name, char *path);
void			ft_recursion_ls(t_list *file, t_als *arg, char *path);
void			ls_dirs(t_list *dirs, t_als *arg, int flag, char *path);
void			ft_sort_rev(t_item *inf, int len);
void			ft_display_total(t_item *inf, int len);
int				ft_max_size(t_item *inf, int len);
void			ft_print_rights(t_item inf);
void			ft_item_del(t_item *inf, int len);
char			*ft_path(t_item *inf, int len, int flag, int i);
int				ft_get_attr(t_item *inf, int len);
int				ft_link(t_item inf);
void			ft_error_perm(char *s);
void			ft_time(t_item inf, t_als *arg);
int				ft_nlink(t_item *inf, int len);
t_view			*ft_makeview(t_item *inf, t_als *arg, int len);
void			ft_print_mode(t_item inf);
int				ft_find_min(t_item *inf, int len, int flag);
void			ft_print_size(t_item inf, t_view *view);
int				ft_find_mor(t_item *inf, int len);

#endif
