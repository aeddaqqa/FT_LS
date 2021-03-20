/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaqqa <aeddaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 01:53:59 by aeddaqqa          #+#    #+#             */
/*   Updated: 2019/11/29 06:13:46 by aeddaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		usage(char **str)
{
	ft_putstr("usage : ft_ls [-Rlart] [file...]");
	write(1, "\n", 1);
	free(*str);
	exit(0);
}

void		flags(char *str, char *res)
{
	int i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'R' && str[i] != 'l'
				&& str[i] != 'r' && str[i] != 't' && str[i] != 'a')
			usage(&res);
		if (str[i] == 'l')
			res[0] = 'a';
		else if (str[i] == 't')
			res[1] = 'a';
		else if (str[i] == 'R')
			res[2] = 'a';
		else if (str[i] == 'r')
			res[3] = 'a';
		else if (str[i] == 'a')
			res[4] = 'a';
		i++;
	}
}

void		ft_aff_error(t_arg *arg, int size)
{
	int		j;
	char	*tmp;

	j = -1;
	while (++j < size)
	{
		if (arg[j].forme == -1)
		{
			tmp = ft_strjoin("./ft_ls: ", arg[j].name);
			perror(tmp);
			free(tmp);
		}
	}
}

int			flags_calc(char *str)
{
	int res;

	res = 0;
	if (str[1] == 'a')
		res += 1;
	if (str[3] == 'a')
		res += 4;
	return (res);
}

int			main(int ac, char **av)
{
	int		i;
	int		res;
	char	*flag;
	t_arg	*arg;
	int		v;

	flag = ft_strdup("zzzzz");
	if (ac > 1 && av)
	{
		ft_flags_param(av, &res, &i, &flag);
		if (!av[i])
			ft_ls(".", res, flag, ".");
		else
		{
			arg = ft_gest_param(&av[i], ac - i, &v, flag[0]);
			ft_sort_arg(&arg, ac - i, flag);
			ft_aff_error(arg, ac - i);
			ft_aff_argf(arg, flag, ac - i, v);
			ft_aff_total(&arg, ac - i, flag, v);
		}
	}
	else
		ft_ls(".", 8, flag, ".");
	free(flag);
	return (0);
}
