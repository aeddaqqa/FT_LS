/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaqqa <aeddaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 01:58:12 by aeddaqqa          #+#    #+#             */
/*   Updated: 2019/11/29 01:14:32 by aeddaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_flags_param(char **av, int *res, int *i, char **flag)
{
	*i = 1;
	while (av[*i] && av[*i][0] == '-' && (ft_strcmp("--", av[*i]) != 0))
	{
		if (ft_strlen(av[*i]) == 1)
			break ;
		flags(av[*i], *flag);
		*i += 1;
	}
	if (av[*i] && (ft_strlen(av[*i]) > 2) && av[*i][0] == '-'
			&& av[*i][1] == '-')
		usage(&*flag);
	*res = flags_calc(*flag);
	if (av[*i] && !ft_strcmp(av[*i], "--"))
		*i += 1;
}

void		ft_help_gp2(char *av, char flag, t_arg **aa, struct stat buf)
{
	char		*str;
	DIR			*dir;
	t_arg		*a;

	a = *aa;
	dir = opendir(av);
	str = str_mod(buf.st_mode);
	if (flag != 'z' && lstat(av, &buf) != -1 &&
			av[ft_strlen(av) - 1] != '/' && str[0] == 'l')
		a->forme = 1;
	else if (dir == NULL && (lstat(av, &buf)) != -1 && str[0] != 'd')
		a->forme = 1;
	else if (dir == NULL)
		a->forme = -1;
	else
		a->forme = 0;
	if (str)
		free(str);
	if (dir)
		closedir(dir);
}

void		ft_help_gp(char *av, char flag, t_arg *a, int **v)
{
	struct stat	buf;
	DIR			*dir;

	dir = opendir(av);
	if (((lstat(av, &buf) == -1) && (dir == NULL)))
	{
		a->forme = -1;
		a->time = 0;
	}
	else
	{
		a->time = buf.st_mtimespec.tv_sec;
		ft_help_gp2(av, flag, &a, buf);
		if (a->forme == 0)
			**v += 1;
	}
	if (dir)
		closedir(dir);
}

t_arg		*ft_gest_param(char **av, int size, int *v, char flag)
{
	t_arg		*l;
	int			i;

	*v = 0;
	if (!(l = malloc(sizeof(t_arg) * size)))
		return (NULL);
	i = 0;
	while (av[i])
	{
		l[i].name = av[i];
		ft_help_gp(av[i], flag, &l[i], &v);
		i++;
	}
	return (l);
}
