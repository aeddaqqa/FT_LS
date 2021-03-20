/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaqqa <aeddaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 01:56:42 by aeddaqqa          #+#    #+#             */
/*   Updated: 2019/11/29 03:57:35 by aeddaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_is_gvu(char **str, mode_t buf)
{
	if (S_ISUID & buf)
	{
		if ((*str)[3] == 'x')
			(*str)[3] = 's';
		else
			(*str)[3] = 'S';
	}
	if (S_ISGID & buf)
	{
		if ((*str)[6] == 'x')
			(*str)[6] = 's';
		else
			(*str)[6] = 'S';
	}
	if (S_ISVTX & buf)
	{
		if ((*str)[9] == 'x')
			(*str)[9] = 't';
		else
			(*str)[9] = 'T';
	}
}

char			*ft_insert_type(mode_t buf)
{
	char *str;

	str = ft_strnew(10);
	if (str)
	{
		if ((S_ISDIR(buf)))
			str[0] = 'd';
		else if ((S_ISCHR(buf)))
			str[0] = 'c';
		else if ((S_ISBLK(buf)))
			str[0] = 'b';
		else if ((S_ISFIFO(buf)))
			str[0] = 'p';
		else if ((S_ISSOCK(buf)))
			str[0] = 's';
		else if ((S_ISLNK(buf)))
			str[0] = 'l';
		else
			str[0] = '-';
		return (str);
	}
	return (NULL);
}

char			*str_mod(mode_t buf)
{
	int		i;
	char	*str;
	char	*chars;

	chars = "rwxrwxrwx";
	str = ft_insert_type(buf);
	if (!str)
		return (NULL);
	i = 1;
	while (i < 10)
	{
		str[i] = (buf & (1 << (8 - (i - 1)))) ? chars[i - 1] : '-';
		i++;
	}
	ft_is_gvu(&str, buf);
	str[i] = '\0';
	return (str);
}

void			ft_switch(t_arg *a, t_arg *b)
{
	t_arg tmp;

	tmp.name = a->name;
	tmp.time = a->time;
	tmp.forme = a->forme;
	a->name = b->name;
	a->time = b->time;
	a->forme = b->forme;
	b->name = tmp.name;
	b->time = tmp.time;
	b->forme = tmp.forme;
}

t_lst			*ft_copy_elem(t_lst *l)
{
	t_lst *new;

	if (!(new = (t_lst *)malloc(sizeof(t_lst))))
		return (NULL);
	new->next = NULL;
	new->name = ft_strdup(l->name);
	new->path = ft_strdup(l->path);
	new->buf = l->buf;
	return (new);
}
