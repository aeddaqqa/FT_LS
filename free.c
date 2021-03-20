/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaqqa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 03:18:22 by aeddaqqa          #+#    #+#             */
/*   Updated: 2019/11/26 00:52:36 by aeddaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_free_ls(t_lst **ls)
{
	t_lst	*tmp;
	t_lst	*lst;

	lst = *ls;
	while (lst)
	{
		tmp = lst->next;
		free(lst->name);
		free(lst->path);
		free(lst);
		lst = tmp;
	}
	*ls = NULL;
}

void	ft_free_dir(t_dir **dir)
{
	t_dir	*tmp;
	t_dir	*d;

	d = *dir;
	while (d)
	{
		tmp = d->next;
		free(d);
		d = tmp;
	}
}

void	ft_free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_arg(t_arg **arg, int size)
{
	int		i;
	t_arg	*t;

	i = 0;
	t = *arg;
	i = size;
	free(t);
	i++;
}
