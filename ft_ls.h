/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaqqa <aeddaqqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:01:33 by aeddaqqa          #+#    #+#             */
/*   Updated: 2019/11/28 07:42:57 by aeddaqqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <math.h>
# include <stdio.h>
# define MAJOR(dev) ((unsigned int) ((dev) >> 24))
# define MINOR(dev) ((unsigned int) ((dev) & 0xff))

typedef struct		s_lst
{
	char			*name;
	char			*path;
	struct stat		buf;
	struct s_lst	*next;
}					t_lst;

typedef struct		s_len
{
	unsigned int	link_l;
	unsigned int	owner_l;
	unsigned int	grp_l;
	unsigned int	sfile_l;
	unsigned int	major_l;
	unsigned int	minor_l;
}					t_len;

typedef struct		s_dir
{
	char			*name;
	char			*path;
	struct s_dir	*next;
}					t_dir;

typedef	struct		s_ls
{
	t_lst	*lst;
	t_dir	*rec;
	t_lst	*tmp1;
	t_len	len;
	int		b;
}					t_ls;

typedef struct		s_arg
{
	char			*name;
	unsigned int	time;
	int				forme;
	char			*error;
}					t_arg;

t_arg				*ft_gest_param(char **av, int size, int *v, char flag);
t_lst				*ft_tri(t_lst **lst, int v, int i);
int					ft_int_len(int n);
unsigned int		ft_list_size(t_lst *lst);
t_lst				*ft_new_elem(char *name_file, char *path);
char				*ft_user_id(uid_t st_uid);
char				*ft_grp_id(gid_t st_gid);
void				ft_init_len(t_len *len_t);
void				ft_cmp_len(t_len *len_t, struct stat buf);
void				ft_final_form(t_len *len_t);
void				ft_aff_l(t_lst *lst, t_len len_t, int blocks, char flag);
char				*str_mod(mode_t buf);
t_ls				ft_stock(char *av, DIR *dir, char flag);
t_lst				*ft_copy_elem(t_lst *l);
void				ft_aff(t_lst *lst, char flag);
t_dir				*ft_copy_dir(char *name, char *path);
char				*ft_join_path(char *s1, char *s2);
void				ft_free_ls(t_lst **lst);
void				ft_free_dir(t_dir **lst);
void				ft_free_tab(char **tab);
t_dir				*ft_dir(t_lst *l, char flag);
void				ft_sort_arg(t_arg **tab, int size, char *flag);
void				ft_aff_hp(t_arg arg, t_len li, struct stat buf);
void				ft_aff_argf(t_arg *arg, char *flag, int size, int v);
void				ft_free_arg(t_arg **arg, int size);
void				ft_help_aff(t_lst *lst, t_len len_t);
char				*ft_get_link(char *path);
int					ft_check_link(char *av, char flag);
void				ft_switch(t_arg *a, t_arg *b);
char				*ft_insert_type(mode_t buf);
void				ft_is_gvu(char **str, mode_t buf);
void				ft_ls_1(t_ls *l, char *flag, int res);
void				ft_ls(char *av, int res, char *flag, char *name);
void				ft_flags_param(char **av, int *res, int *i, char **flag);
int					flags_calc(char *str);
void				flags(char *str, char *res);
void				usage(char **str);
void				ft_aff_error(t_arg *arg, int size);
void				ft_aff_total(t_arg **arg, int size, char *flag, int v);
void				ft_mtr_p1(t_lst **l, t_lst **r, t_lst **res);
void				ft_mtr_p2(t_lst **l, t_lst **r, t_lst **tmp);
void				ft_mt_p1(t_lst **l, t_lst **r, t_lst **res);
void				ft_mt_p2(t_lst **l, t_lst **r, t_lst **tmp);
void				ft_mar_p1(t_lst **l, t_lst **r, t_lst **res);
void				ft_mar_p2(t_lst **l, t_lst **r, t_lst **tmp);
void				ft_ma_p2(t_lst **l, t_lst **r, t_lst **tmp);
void				ft_ma_p1(t_lst **l, t_lst **r, t_lst **res);
void				ft_help_aff_p1(t_lst *lst, t_len len_t, char **link);
void				ft_help_aff_p2(t_lst *lst, t_len len_t);
void				ft_help_aff_p3(t_lst *lst);
void				ft_aff_hp_p1(t_len len_t, struct stat buf);
void				ft_aff_hp_p2(struct stat buf);

#endif
