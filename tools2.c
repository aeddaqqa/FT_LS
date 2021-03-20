/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaqqa <aeddaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 01:56:25 by aeddaqqa          #+#    #+#             */
/*   Updated: 2019/11/29 19:38:39 by aeddaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_init_len(t_len *len_t)
{
	len_t->link_l = 0;
	len_t->owner_l = 0;
	len_t->grp_l = 0;
	len_t->sfile_l = 0;
	len_t->major_l = 0;
	len_t->minor_l = 0;
}

void			ft_cmp_len(t_len *len_t, struct stat buf)
{
	unsigned int	v;

	if (len_t->link_l < buf.st_nlink)
		len_t->link_l = buf.st_nlink;
	if (len_t->sfile_l < buf.st_size)
		len_t->sfile_l = buf.st_size;
	if (len_t->owner_l < (v = ft_strlen(ft_user_id(buf.st_uid))))
		len_t->owner_l = v;
	if (len_t->grp_l < (v = ft_strlen(ft_grp_id(buf.st_gid))))
		len_t->grp_l = v;
	if ((S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode)))
	{
		if ((len_t->major_l < (v = MAJOR(buf.st_rdev))))
			len_t->major_l = v;
		if ((len_t->minor_l < (v = MINOR(buf.st_rdev))))
			len_t->minor_l = v;
	}
}

void			ft_final_form(t_len *len_t)
{
	len_t->link_l = ft_int_len(len_t->link_l) + 1;
	len_t->major_l = ft_int_len(len_t->major_l);
	len_t->minor_l = ft_int_len(len_t->minor_l);
	len_t->sfile_l = ft_int_len(len_t->sfile_l) +
		len_t->major_l + len_t->minor_l - 3;
	len_t->owner_l += 2;
	len_t->grp_l += 1;
}

int				ft_int_len(int n)
{
	int cmp;
	int k;

	if (n == 0)
		return (1);
	cmp = 0;
	k = n;
	while (k)
	{
		cmp++;
		k /= 10;
	}
	if (n < 0)
		cmp++;
	return (cmp);
}

unsigned int	ft_list_size(t_lst *l)
{
	unsigned int	size;

	size = 0;
	while (l)
	{
		l = l->next;
		size++;
	}
	return (size);
}
