/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 13:32:12 by skavunen          #+#    #+#             */
/*   Updated: 2017/04/28 14:50:49 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			main(int argc, char **argv)
{
	t_als	*arg;
	t_list	*list;

	arg = ft_newarg();
	list = NULL;
	if (argc > 1)
		ft_get_params(argc - 1, argv, arg, list);
	else
	{
		ft_lstpushback(&list, ".", 2);
		ft_ls(arg, list, 0);
	}
	return (0);
}
