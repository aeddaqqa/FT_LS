/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_fs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaqqa <aeddaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 03:04:03 by aeddaqqa          #+#    #+#             */
/*   Updated: 2019/11/29 06:13:47 by aeddaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_aff_hp_p1(t_len len_t, struct stat buf)
{
	unsigned int	i;
	char			*str;
	unsigned int	len;

	str = str_mod(buf.st_mode);
	ft_putstr(str);
	free(str);
	i = 0;
	len = ft_int_len(buf.st_nlink) + 1;
	while (i++ < len_t.link_l - len)
		write(1, " ", 1);
	ft_putnbr(buf.st_nlink);
	i = 0;
	write(1, " ", 1);
	str = ft_user_id(buf.st_uid);
	ft_putstr(str);
	len = ft_strlen(str);
	while (i++ < (len_t.owner_l - len))
		write(1, " ", 1);
	str = ft_grp_id(buf.st_gid);
	ft_putstr(str);
	len = ft_strlen(str);
	i = 0;
	while (i++ < (len_t.grp_l - len))
		write(1, " ", 1);
}

void		ft_aff_hp_p2(struct stat buf)
{
	char			**tab;
	unsigned int	time_c;
	unsigned int	i;

	time_c = time(NULL);
	tab = ft_strsplit(ctime(&buf.st_mtimespec.tv_sec), ' ');
	ft_putstr(tab[1]);
	ft_putstr(" ");
	if (ft_strlen(tab[2]) <= 1)
		write(1, " ", 1);
	ft_putstr(tab[2]);
	ft_putstr(" ");
	i = 0;
	if (time_c - buf.st_mtimespec.tv_sec >= 15778476 ||
			time_c - buf.st_mtimespec.tv_sec <= -15778476)
	{
		ft_putchar(' ');
		while (i < 4)
			ft_putchar(tab[4][i++]);
	}
	else
		while (i < 5)
			ft_putchar(tab[3][i++]);
	ft_free_tab(tab);
	ft_putstr(" ");
}

void		ft_aff_hp(t_arg arg, t_len len_t, struct stat buf)
{
	unsigned int	i;
	char			*link;

	link = ft_get_link(arg.name);
	ft_aff_hp_p1(len_t, buf);
	i = 0;
	while (i++ < len_t.sfile_l - ft_int_len(buf.st_size) + 1)
		write(1, " ", 1);
	ft_putnbr(buf.st_size);
	ft_putstr(" ");
	ft_aff_hp_p2(buf);
	ft_putstr(arg.name);
	if (link)
	{
		ft_putstr(" -> ");
		ft_putstr(link);
		free(link);
	}
	write(1, "\n", 1);
}

void		ft_aff_flagl(t_arg *arg, int *x, int size)
{
	t_len		l;
	struct stat	buf;
	int			i;

	ft_init_len(&l);
	i = -1;
	while (++i < size)
	{
		if (arg[i].forme == 1)
		{
			*x += 1;
			lstat(arg[i].name, &buf);
			ft_cmp_len(&l, buf);
		}
	}
	ft_final_form(&l);
	i = -1;
	while (++i < size)
	{
		if (arg[i].forme == 1)
		{
			lstat(arg[i].name, &buf);
			ft_aff_hp(arg[i], l, buf);
		}
	}
}

void		ft_aff_argf(t_arg *arg, char *flag, int size, int v)
{
	int			i;
	int			x;

	x = 0;
	i = 0;
	if (flag[0] != 'a')
	{
		while (i < size)
		{
			if (arg[i].forme == 1)
			{
				ft_putendl(arg[i].name);
				x++;
			}
			i++;
		}
	}
	else
		ft_aff_flagl(arg, &x, size);
	if (x && v)
		write(1, "\n", 1);
}
