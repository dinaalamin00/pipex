/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diahmed <diahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:25:06 by diahmed           #+#    #+#             */
/*   Updated: 2024/01/09 12:47:20 by diahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	open_error(char *fname, t_pip_b pip, int mode)
{
	if (mode == 0)
	{
		if (pip.stat_in != 1)
			put_error_b(fname);
		else
			exit(EXIT_FAILURE);
	}
	else
	{
		if (pip.stat_out != 1)
			put_error_b(fname);
		else
		{
			close(0);
			exit(EXIT_FAILURE);
		}
	}
}

int	open_fd(char *fname, t_pip_b pip, int mode)
{
	int	fd;

	if (mode == 0)
	{
		fd = open(fname, O_RDONLY, 0644);
		if (fd < 0)
			open_error(fname, pip, mode);
		else
			return (fd);
	}
	else
	{
		fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			open_error(fname, pip, mode);
		else
			return (fd);
	}
	exit(EXIT_FAILURE);
}

static int	fd_open_check(int ac, char **av, int mode)
{
	int	fd;

	if (mode == 0)
	{
		fd = open(av[1], O_RDONLY, 0644);
		if (fd != -1)
			close(fd);
		else
		{
			perror(av[1]);
			return (1);
		}
	}
	else
	{
		fd = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd != -1)
			close(fd);
		else
		{
			perror(av[ac - 1]);
			return (1);
		}
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_pip_b	pip;

	if (ac < 5)
		print_error_b("Incorrect number of arguments");
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		if (ac < 6)
			print_error_b("Incorrect number of arguments");
		put_in_file(av);
		pip.stat_out = fd_open_check(ac, av, 1);
		pip.i = 3;
	}
	else
	{
		pip.stat_in = fd_open_check(ac, av, 0);
		pip.stat_out = fd_open_check(ac, av, 1);
		pip.in_fd = open_fd(av[1], pip, 0);
		if (dup2(pip.in_fd, STDIN_FILENO) < 0)
			put_error_b("Error duplicating file descriptor");
		close(pip.in_fd);
		pip.i = 2;
	}
	do_pip(ac, av, pip, env);
	return (0);
}
