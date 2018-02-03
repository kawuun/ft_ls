/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 15:30:09 by skavunen          #+#    #+#             */
/*   Updated: 2017/04/28 15:32:48 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_als		*ft_newarg(void)
{
	t_als	*arg;

	arg = (t_als*)malloc(sizeof(t_als));
	arg->l = 0;
	arg->br = 0;
	arg->r = 0;
	arg->a = 0;
	arg->t = 0;
	arg->d = 0;
	arg->f = 0;
	arg->u = 0;
	arg->n = 0;
	arg->o = 0;
	return (arg);
}

int			ft_isflag(char c)
{
	if (c == 'a' || c == 'r' || c == 'l' || c == 't' || c == 'R'
		|| c == 'd' || c == 'f' || c == 'u' || c == 'n' || c == 'o')
		return (1);
	return (0);
}

int			ft_checkflag(char *s)
{
	if (s && s[0] == '-' && s[1])
		return (1);
	return (0);
}

void		ft_setflag(t_als *arg, char *s)
{
	int		i;

	i = 0;
	while (s[++i])
	{
		if (ft_isflag(s[i]) || (s[1] == '-' && s[2] == '\0'))
		{
			arg->a = (s[i] == 'a' ? 1 : arg->a);
			arg->r = (s[i] == 'r' ? 1 : arg->r);
			arg->l = (s[i] == 'l' ? 1 : arg->l);
			arg->t = (s[i] == 't' ? 1 : arg->t);
			arg->br = (s[i] == 'R' ? 1 : arg->br);
			arg->d = (s[i] == 'd' ? 1 : arg->d);
			arg->f = (s[i] == 'f' ? 1 : arg->f);
			arg->u = (s[i] == 'u' ? 1 : arg->u);
			arg->n = (s[i] == 'n' ? 1 : arg->n);
			arg->o = (s[i] == 'o' ? 1 : arg->o);
		}
		else
			ft_error_arg(s[i]);
	}
}

void		ft_get_params(int nb, char **s, t_als *arg, t_list *list)
{
	int		i;

	i = 0;
	while (ft_checkflag(s[++i]))
		ft_setflag(arg, s[i]);
	if (i == 0)
		i += 1;
	while (i <= nb)
	{
		ft_lstpushback(&list, s[i], ft_strlen(s[i]) + 1);
		i++;
	}
	if (!list)
		ft_lstpushback(&list, ".", 2);
	ft_ls(arg, list, 0);
}
