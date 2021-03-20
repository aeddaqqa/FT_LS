/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_l.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaqqa <aeddaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 02:38:37 by aeddaqqa          #+#    #+#             */
/*   Updated: 2019/11/29 06:13:44 by aeddaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_help_aff_p1(t_lst *lst, t_len len_t, char **link)
{
	char			*str;
	unsigned int	i;
	int				v;

	str = str_mod(lst->buf.st_mode);
	if (str[0] == 'l')
		(*link) = ft_get_link(lst->path);
	ft_putstr(str);
	free(str);
	i = 0;
	while (i++ < len_t.link_l - ft_int_len(lst->buf.st_nlink))
		write(1, " ", 1);
	ft_putnbr(lst->buf.st_nlink);
	i = 0;
	write(1, " ", 1);
	str = ft_user_id(lst->buf.st_uid);
	ft_putstr(str);
	while (i++ < (len_t.owner_l - ft_strlen(str)))
		write(1, " ", 1);
	i = 0;
	str = ft_grp_id(lst->buf.st_gid);
	ft_putstr(str);
	v = ft_strlen(str);
	while (i++ < (len_t.grp_l - v))
		write(1, " ", 1);
}

void		ft_help_aff_p21(t_lst *lst, t_len len_t)
{
	unsigned int	z;
	unsigned int	j;
	unsigned int	i;

	i = 0;
	if (len_t.major_l > 1 || len_t.minor_l > 1)
		z = 0;
	else
		z = 3;
	j = ft_int_len(lst->buf.st_size);
	while (i++ < len_t.sfile_l + z - j)
		write(1, " ", 1);
	ft_putnbr(lst->buf.st_size);
}

void		ft_help_aff_p2(t_lst *lst, t_len len_t)
{
	unsigned int	i;
	unsigned int	z;
	unsigned int	j;

	i = 0;
	if ((S_ISCHR(lst->buf.st_mode) || S_ISBLK(lst->buf.st_mode)))
	{
		j = MAJOR(lst->buf.st_rdev);
		z = ft_int_len(j);
		while (i++ < (len_t.major_l - z))
			write(1, " ", 1);
		ft_putnbr(j);
		write(1, ", ", 2);
		i = 0;
		j = MINOR(lst->buf.st_rdev);
		z = ft_int_len(j);
		while (i++ < (len_t.minor_l - z))
			write(1, " ", 1);
		ft_putnbr(j);
	}
	else
		ft_help_aff_p21(lst, len_t);
	ft_putstr(" ");
}

void		ft_help_aff_p3(t_lst *lst)
{
	char	**tab;
	int		time_c;
	int		i;

	time_c = time(NULL);
	tab = ft_strsplit(ctime(&lst->buf.st_mtimespec.tv_sec), ' ');
	ft_putstr(tab[1]);
	ft_putstr(" ");
	if (ft_strlen(tab[2]) <= 1)
		write(1, " ", 1);
	ft_putstr(tab[2]);
	ft_putstr(" ");
	i = 0;
	if ((time_c - lst->buf.st_mtimespec.tv_sec >= 15778476) ||
			(time_c - lst->buf.st_mtimespec.tv_sec <= -15778476))
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

void		ft_help_aff(t_lst *lst, t_len len_t)
{
	char			*link;

	link = NULL;
	if (lst)
	{
		ft_help_aff_p1(lst, len_t, &link);
		ft_help_aff_p2(lst, len_t);
		ft_help_aff_p3(lst);
		ft_putstr(lst->name);
		if (link)
		{
			ft_putstr(" -> ");
			ft_putstr(link);
			free(link);
		}
		write(1, "\n", 1);
	}
}
