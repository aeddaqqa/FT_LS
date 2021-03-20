/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaqqa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 02:28:47 by aeddaqqa          #+#    #+#             */
/*   Updated: 2019/11/28 20:09:06 by aeddaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_lst	*ft_merge_t_r(t_lst **ls, t_lst **rs)
{
	t_lst	*res;
	t_lst	*tmp;
	t_lst	*l;
	t_lst	*r;

	l = *ls;
	r = *rs;
	ft_mtr_p1(&l, &r, &res);
	tmp = res;
	ft_mtr_p2(&l, &r, &tmp);
	while (l)
	{
		tmp->next = ft_copy_elem(l);
		l = l->next;
		tmp = tmp->next;
	}
	while (r)
	{
		tmp->next = ft_copy_elem(r);
		r = r->next;
		tmp = tmp->next;
	}
	ft_free_ls(ls);
	ft_free_ls(rs);
	return (res);
}

static t_lst	*ft_merge_t(t_lst **ls, t_lst **rs)
{
	t_lst	*res;
	t_lst	*tmp;
	t_lst	*l;
	t_lst	*r;

	l = *ls;
	r = *rs;
	ft_mt_p1(&l, &r, &res);
	tmp = res;
	ft_mt_p2(&l, &r, &tmp);
	while (l)
	{
		tmp->next = ft_copy_elem(l);
		l = l->next;
		tmp = tmp->next;
	}
	while (r)
	{
		tmp->next = ft_copy_elem(r);
		r = r->next;
		tmp = tmp->next;
	}
	ft_free_ls(ls);
	ft_free_ls(rs);
	return (res);
}

static t_lst	*ft_merge_a_r(t_lst **ls, t_lst **rs)
{
	t_lst	*res;
	t_lst	*tmp;
	t_lst	*l;
	t_lst	*r;

	l = *ls;
	r = *rs;
	ft_mar_p1(&l, &r, &res);
	tmp = res;
	ft_mar_p2(&l, &r, &tmp);
	while (l)
	{
		tmp->next = ft_copy_elem(l);
		l = l->next;
		tmp = tmp->next;
	}
	while (r)
	{
		tmp->next = ft_copy_elem(r);
		r = r->next;
		tmp = tmp->next;
	}
	ft_free_ls(ls);
	ft_free_ls(rs);
	return (res);
}

static t_lst	*ft_merge_a(t_lst **ls, t_lst **rs)
{
	t_lst	*res;
	t_lst	*tmp;
	t_lst	*l;
	t_lst	*r;

	l = *ls;
	r = *rs;
	ft_ma_p1(&l, &r, &res);
	tmp = res;
	ft_ma_p2(&l, &r, &tmp);
	while (l)
	{
		tmp->next = ft_copy_elem(l);
		l = l->next;
		tmp = tmp->next;
	}
	while (r)
	{
		tmp->next = ft_copy_elem(r);
		r = r->next;
		tmp = tmp->next;
	}
	ft_free_ls(ls);
	ft_free_ls(rs);
	return (res);
}

t_lst			*ft_tri(t_lst **lst, int v, int i)
{
	int				size;
	t_lst			*r;
	t_lst			*l;

	i = -1;
	size = ft_list_size(*lst);
	if (size < 2)
		return (*lst);
	l = *lst;
	r = (*lst)->next;
	while (++i < (size / 2) - 1)
	{
		r = r->next;
		l = l->next;
	}
	l->next = NULL;
	l = ft_tri(&(*lst), v, i);
	r = ft_tri(&r, v, i);
	if (v == 5)
		return (ft_merge_t_r(&l, &r));
	if (v == 1)
		return (ft_merge_t(&l, &r));
	if (v == 4)
		return (ft_merge_a_r(&l, &r));
	return (ft_merge_a(&l, &r));
}
