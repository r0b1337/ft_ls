/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 16:31:22 by rdurst            #+#    #+#             */
/*   Updated: 2018/05/17 17:45:00 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <sys/stat.h>
# include <stdio.h>
# include <time.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <dirent.h>
# include "../libft/libft.h"

typedef struct		s_options
{
	int				l;
	int				R;
	int				a;
	int				r;
	int				t;
}					t_options;

typedef struct		s_padding
{
	int				directory_number;
	int				perms;
	int				links;
	int				user;
	int				group;
	int				size;
	int				timestamp;
	int				name;
}					t_padding;

typedef struct		s_file
{
	char			*name;
	char			*perms;
	int				links;
	char			*user;
	char			*group;
	int				size;
	long			timestamp;
	int			blocks;
}					t_file;

char				*find_filetype(struct stat *file);
char				*find_modes(struct stat *file);
int					option_l(t_file **dir, int size, t_options *options, t_padding *pad, int files);
void				option_t(t_file **dir, int size);
void				no_padding(t_file **dir, int size, t_options *options);
void					handle_options(t_file **dir, int size, t_options *options,  t_padding *pad, int files);
char				*valid_path(char *path);
int					neutral_ls(char *name, t_options *options);
t_options			*init_options(int ac, char **av);
void				fill_options(t_options *options, char *arg);
t_padding			*init_padding(void);
t_padding			*fill_padding(t_padding *padding, t_file **dir, int size);
void				print_spaces(int nb);
int				ft_dirlen(char *name, char *path);
t_file				**init_dir(t_file **dir, int size);
char				*find_user(struct stat *stats);
char				*find_group(struct stat *stats);
void				print_timestamp(long timestamp);
t_file				**fill_dir(t_file **dir, int size, char *path);
t_file				**fill_files(char **av, int begin, int size, t_file **dir);
int				valid_arg(char *arg);
void				print_blocks(t_file **dir, int size);
void				sort_dir(t_file **dir, int size);
void				reverse_dir(t_file **dir, int size);
void				treat_args(char **av, int begin, t_options *options);
void				treat_dirs(char **av, int begin, t_options *options);
int				count_dirs(char **av, int begin);
int				count_files(char **av, int begin);
int				single_files_ls(char **av, int begin, t_options *options);
void				sort_args(char **av, int begin);
void				reverse_args(char **av);
void				sort_by_time(char **av, int begin);
void				lexical_order(t_file **dir, int size);

#endif
