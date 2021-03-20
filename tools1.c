/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaqqa <aeddaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 01:56:11 by aeddaqqa          #+#    #+#             */
/*   Updated: 2019/11/29 06:13:40 by aeddaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*ft_user_id(uid_t st_uid)
{
	struct passwd *pwd;

	if (!(pwd = getpwuid(st_uid)))
		return (NULL);
	return (pwd->pw_name);
}

char		*ft_grp_id(gid_t st_gid)
{
	struct group *grp;

	if (!(grp = getgrgid(st_gid)))
		return (NULL);
	return (grp->gr_name);
}

void		ft_linknx(char *av)
{
	t_lst	*l;
	t_len	len;

	l = ft_new_elem(ft_strdup(av), ft_strdup(av));
	lstat(av, &l->buf);
	ft_init_len(&len);
	ft_cmp_len(&len, l->buf);
	ft_final_form(&len);
	ft_help_aff(l, len);
	ft_free_ls(&l);
}

int			ft_check_link(char *av, char flag)
{
	DIR			*dir;
	struct stat	buf;
	char		*link;

	if (flag != 'z')
	{
		if (lstat(av, &buf) != -1 && av[ft_strlen(av) - 1] != '/')
		{
			if ((S_ISLNK(buf.st_mode)))
			{
				link = ft_get_link(av);
				if ((dir = opendir(link)))
				{
					ft_linknx(av);
					closedir(dir);
				}
				if (link)
					free(link);
				return (1);
			}
		}
	}
	return (0);
}

char		*ft_get_link(char *path)
{
	char	*str;
	int		r;

	if (!(str = (char*)malloc(sizeof(char) * 1024)))
		return (NULL);
	if ((r = readlink(path, str, 1023)) == -1)
	{
		free(str);
		return (NULL);
	}
	str[r] = '\0';
	return (str);
}
