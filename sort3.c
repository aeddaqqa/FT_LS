/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaqqa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 02:34:48 by aeddaqqa          #+#    #+#             */
/*   Updated: 2019/11/28 02:35:13 by aeddaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_mt_p1(t_lst **l, t_lst **r, t_lst **res)
{
	if (((*l)->buf.st_mtimespec.tv_sec < (*r)->buf.st_mtimespec.tv_sec))
	{
		(*res) = ft_copy_elem((*r));
		(*r) = (*r)->next;
	}
	else if (((*l)->buf.st_mtimespec.tv_sec > (*r)->buf.st_mtimespec.tv_sec))
	{
		(*res) = ft_copy_elem((*l));
		(*l) = (*l)->next;
	}
	else
	{
		if ((ft_strcmp((*l)->name, (*r)->name)) > 0)
		{
			(*res) = ft_copy_elem((*r));
			(*r) = (*r)->next;
		}
		else
		{
			(*res) = ft_copy_elem((*l));
			(*l) = (*l)->next;
		}
	}
}

void	ft_name_cmp(t_lst ***l, t_lst ***r, t_lst ***tmp)
{
	if ((ft_strcmp((**l)->name, (**r)->name)) > 0)
	{
		(**tmp)->next = ft_copy_elem((**r));
		(**r) = (**r)->next;
	}
	else
	{
		(**tmp)->next = ft_copy_elem((**l));
		(**l) = (**l)->next;
	}
}

void	ft_mt_p2(t_lst **l, t_lst **r, t_lst **tmp)
{
	while ((*l) && (*r))
	{
		if (((*l)->buf.st_mtimespec.tv_sec < (*r)->buf.st_mtimespec.tv_sec))
		{
			(*tmp)->next = ft_copy_elem((*r));
			(*r) = (*r)->next;
		}
		else if ((*l)->buf.st_mtimespec.tv_sec > (*r)->buf.st_mtimespec.tv_sec)
		{
			(*tmp)->next = ft_copy_elem((*l));
			(*l) = (*l)->next;
		}
		else
			ft_name_cmp(&l, &r, &tmp);
		(*tmp) = (*tmp)->next;
	}
}

void	ft_ma_p1(t_lst **l, t_lst **r, t_lst **res)
{
	if ((ft_strcmp((*l)->name, (*r)->name)) > 0)
	{
		(*res) = ft_copy_elem((*r));
		(*r) = (*r)->next;
	}
	else
	{
		(*res) = ft_copy_elem((*l));
		(*l) = (*l)->next;
	}
}

void	ft_ma_p2(t_lst **l, t_lst **r, t_lst **tmp)
{
	while ((*l) && (*r))
	{
		if ((ft_strcmp((*l)->name, (*r)->name)) > 0)
		{
			(*tmp)->next = ft_copy_elem((*r));
			(*r) = (*r)->next;
		}
		else
		{
			(*tmp)->next = ft_copy_elem((*l));
			(*l) = (*l)->next;
		}
		(*tmp) = (*tmp)->next;
	}
}
