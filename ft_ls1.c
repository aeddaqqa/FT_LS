/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaqqa <aeddaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 02:00:57 by aeddaqqa          #+#    #+#             */
/*   Updated: 2019/11/29 01:08:20 by aeddaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_aff(t_lst *lst, char flag)
{
	while (lst)
	{
		if (flag != 'z' || lst->name[0] != '.')
			ft_putendl(lst->name);
		lst = lst->next;
	}
}

void			ft_aff_l(t_lst *lst, t_len len_t, int blocks, char flag)
{
	if (lst)
	{
		ft_putstr("total ");
		ft_putnbr(blocks);
		write(1, "\n", 1);
		while (lst)
		{
			if (flag == 'a' || lst->name[0] != '.')
				ft_help_aff(lst, len_t);
			lst = lst->next;
		}
	}
}

void			ft_aff_total(t_arg **arge, int size, char *flag, int v)
{
	int		j;
	int		res;
	t_arg	*arg;

	arg = *arge;
	res = flags_calc(flag);
	j = -1;
	while (++j < size)
	{
		if (arg[j].forme == 0)
		{
			if (size - 1 != 0)
			{
				ft_putstr(arg[j].name);
				ft_putstr(":\n");
			}
			ft_ls(arg[j].name, res, flag, arg[j].name);
			if (--v)
				write(1, "\n", 1);
		}
	}
	free(arg);
}

void			ft_ls_1(t_ls *l, char *flag, int res)
{
	t_dir	*d;
	t_dir	*dd;

	l->lst = ft_tri(&l->lst, res, 0);
	if (flag[0] != 'z')
		ft_aff_l(l->lst, l->len, l->b, flag[4]);
	else
		ft_aff(l->lst, flag[4]);
	d = ft_dir(l->lst, flag[4]);
	dd = d;
	if (flag[2] == 'a')
	{
		while (dd)
		{
			write(1, "\n", 1);
			ft_putstr(dd->path);
			ft_putstr(":\n");
			ft_ls(dd->path, res, flag, dd->name);
			dd = dd->next;
		}
	}
	if (d)
		ft_free_dir(&d);
	ft_free_ls(&l->lst);
}

void			ft_ls(char *av, int res, char *flag, char *name)
{
	DIR		*dir;
	t_ls	l;
	char	*err;

	dir = opendir(av);
	if (dir == NULL)
	{
		err = ft_strjoin("./ft_ls: ", name);
		perror(err);
		free(err);
		return ;
	}
	l = ft_stock(av, dir, flag[4]);
	closedir(dir);
	if (l.lst)
		ft_ls_1(&l, flag, res);
}
