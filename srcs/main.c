/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 16:13:57 by rdurst            #+#    #+#             */
/*   Updated: 2018/05/17 17:54:14 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*find_filetype(struct stat *file)
{
	if (S_ISREG(file->st_mode) == 1)
		return ("File");
	if (S_ISDIR(file->st_mode) == 1)
		return ("Directory");
	if (S_ISSOCK(file->st_mode) == 1)
		return ("Socket");
	if (S_ISLNK(file->st_mode) == 1)
		return ("Symbolic link");
	else
		return ("?");
}

char 	*find_modes(struct stat *file)
{
	char *ret;

	ret = ft_strnew(10);
	ret[0] = (S_ISDIR(file->st_mode) ? 'd' : '-');
	ret[1] = (file->st_mode & S_IRUSR ? 'r' : '-');
	ret[2] = (file->st_mode & S_IWUSR ? 'w' : '-');
	ret[3] = (file->st_mode & S_IXUSR ? 'x' : '-');
	ret[4] = (file->st_mode & S_IRGRP ? 'r' : '-');
	ret[5] = (file->st_mode & S_IWGRP ? 'w' : '-');
	ret[6] = (file->st_mode & S_IXGRP ? 'x' : '-');
	ret[7] = (file->st_mode & S_IROTH ? 'r' : '-');
	ret[8] = (file->st_mode & S_IWOTH ? 'w' : '-');
	ret[9] = (file->st_mode & S_IXOTH ? 'x' : '-');
	return (ret);
}

char	*valid_path(char *path)
{
	int i;

	i = 0;
	while (path[i])
		i++;
	if (i == 0 || path[i] == '/')
		return (path);
	else
		return (ft_strjoin(path, "/"));
}

int		neutral_ls(char *name, t_options *options)
{
	DIR 			*current;
	struct dirent	*file;
	t_padding		*padding;

	padding = init_padding();
	if ((current = opendir(name)) == NULL)
	{
		fill_padding(padding, name, "");
		handle_options(name, "", options, padding);
		return (1);
	}
	while ((file = readdir(current)) != NULL)
		fill_padding(padding, file->d_name, name);
	(void)closedir(current);
	current = opendir(name);
	while ((file = readdir(current)) != NULL)
		if (!(file->d_name[0] == '.' && options->a == 0))
			handle_options(file->d_name, name, options, padding);
	(void)closedir(current);
	return (0);
}

int	main(int ac, char **av)
{
	int		counter;
	t_options	*options;
	DIR		*tmp;

	counter = 1;
	options = init_options(ac, av);
	while (av[counter] && av[counter][0] == '-')
		counter++;
	if ((ac - counter) == 0)
		return (neutral_ls(".", options));
	if ((ac - counter) > 0)
	{
		while (av[counter])
		{
			if ((tmp = opendir(av[counter])) != NULL)
			{
				ft_putstr(av[counter]);
				ft_putendl(":");
				(void)closedir(tmp);
			}
			neutral_ls(av[counter++], options);
			if (av[counter])
				ft_putchar('\n');
		}
	}
	return (0);
}
