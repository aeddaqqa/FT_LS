/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaqqa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 02:04:49 by aeddaqqa          #+#    #+#             */
/*   Updated: 2019/11/28 20:10:50 by aeddaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				ft_crhead(char *av, struct dirent *p, t_ls *l, char flag)
{
	char	*path;

	if (p)
	{
		path = ft_join_path(av, p->d_name);
		l->lst = ft_new_elem(ft_strdup(p->d_name), path);
		l->tmp1 = l->lst;
		if (lstat(path, &l->lst->buf) == -1)
		{
			ft_free_ls(&l->lst);
			return (1);
		}
		ft_cmp_len(&l->len, l->lst->buf);
		if (flag != 'z' || p->d_name[0] != '.')
			l->b = l->tmp1->buf.st_blocks;
		return (0);
	}
	return (1);
}

char			*ft_join_path(char *s1, char *s2)
{
	char	*path;
	int		i;
	int		j;
	int		r;

	j = -1;
	i = -1;
	while (s2[++j])
		;
	while (s1[++i])
		;
	if (!(path = (char*)malloc(sizeof(char) * (i + j) + 2)))
		return (NULL);
	r = 0;
	i = 0;
	if ((ft_strcmp("/", s1)) != 0)
		while (s1[i])
			path[r++] = s1[i++];
	path[r++] = '/';
	j = 0;
	while (s2[j])
		path[r++] = s2[j++];
	path[r] = '\0';
	return (path);
}

t_lst			*ft_new_elem(char *name_file, char *path)
{
	t_lst	*new;

	if (!(new = (t_lst*)malloc(sizeof(t_lst))))
		return (NULL);
	new->next = NULL;
	new->name = name_file;
	new->path = path;
	return (new);
}

t_ls			ft_stock(char *av, DIR *dir, char flag)
{
	char			*path;
	struct dirent	*p;
	t_ls			l;

	l.b = 0;
	ft_init_len(&l.len);
	p = readdir(dir);
	if (ft_crhead(av, p, &l, flag) == 1)
		return (l);
	while ((p = readdir(dir)))
	{
		path = ft_join_path(av, p->d_name);
		l.tmp1->next = ft_new_elem(ft_strdup(p->d_name), path);
		if ((lstat(path, &l.tmp1->next->buf)) == -1)
		{
			ft_free_ls(&l.lst);
			return (l);
		}
		ft_cmp_len(&l.len, l.tmp1->next->buf);
		if (flag != 'z' || p->d_name[0] != '.')
			l.b += l.tmp1->next->buf.st_blocks;
		l.tmp1 = l.tmp1->next;
	}
	ft_final_form(&l.len);
	return (l);
}
