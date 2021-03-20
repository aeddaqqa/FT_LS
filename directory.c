/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaqqa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 02:51:32 by aeddaqqa          #+#    #+#             */
/*   Updated: 2019/11/29 01:17:02 by aeddaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir		*ft_copy_dir(char *name, char *path)
{
	t_dir	*new;

	if (!(new = (t_dir*)malloc(sizeof(t_dir))))
		return (NULL);
	new->name = name;
	new->path = path;
	new->next = NULL;
	return (new);
}

t_dir		*ft_help_dir(t_lst **lst, char flag)
{
	t_dir	*tmp;
	t_dir	*r;
	t_lst	*l;

	l = *lst;
	r = ft_copy_dir(l->name, l->path);
	l = l->next;
	tmp = r;
	while (l)
	{
		if ((S_ISDIR(l->buf.st_mode)) && ft_strcmp(".", l->name) != 0
				&& ft_strcmp("..", l->name) != 0)
		{
			if (flag != 'z' || l->name[0] != '.')
			{
				tmp->next = ft_copy_dir(l->name, l->path);
				tmp = tmp->next;
			}
		}
		l = l->next;
	}
	return (r);
}

t_dir		*ft_dir(t_lst *l, char flag)
{
	t_dir	*r;

	r = NULL;
	if (l)
	{
		while (l && (!(S_ISDIR(l->buf.st_mode)) || !ft_strcmp("..", l->name) ||
					!ft_strcmp(".", l->name)))
			l = l->next;
	}
	if (l)
	{
		if (flag != 'a')
		{
			while (l && ((!(S_ISDIR(l->buf.st_mode))) || (l->name[0] == '.')))
				l = l->next;
		}
		if (l)
			r = ft_help_dir(&l, flag);
	}
	return (r);
}

void		ft_sort_flagt(t_arg **table, int size, char flag)
{
	t_arg	*tab;
	int		i;
	int		j;

	tab = *table;
	i = 0;
	while (i < size)
	{
		if (tab[i].forme != -1)
		{
			j = i + 1;
			while (j < size)
			{
				if (tab[j].forme != -1)
				{
					if (flag == 'a' && (tab[i].time > tab[j].time))
						ft_switch(&tab[i], &tab[j]);
					else if (flag != 'a' && tab[i].time < tab[j].time)
						ft_switch(&tab[i], &tab[j]);
				}
				j++;
			}
		}
		i++;
	}
}

void		ft_sort_arg(t_arg **tabl, int size, char *flag)
{
	int i;
	int j;

	i = -1;
	while (++i < size)
	{
		j = i;
		while (++j < size)
		{
			if (((*tabl)[i].forme == -1 && (*tabl)[j].forme == -1) &&
					(ft_strcmp((*tabl)[i].name, (*tabl)[j].name) > 0))
				ft_switch(&(*tabl)[i], &(*tabl)[j]);
			if ((*tabl)[i].forme != -1 && (*tabl)[j].forme != -1)
			{
				if (flag[3] != 'a' &&
						ft_strcmp((*tabl)[i].name, (*tabl)[j].name) > 0)
					ft_switch(&(*tabl)[i], &(*tabl)[j]);
				else if (flag[3] == 'a' &&
						ft_strcmp((*tabl)[i].name, (*tabl)[j].name) < 0)
					ft_switch(&(*tabl)[i], &(*tabl)[j]);
			}
		}
	}
	if (flag[1] == 'a')
		ft_sort_flagt(&(*tabl), size, flag[3]);
}
