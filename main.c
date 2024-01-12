/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diahmed <diahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:58:10 by diahmed           #+#    #+#             */
/*   Updated: 2024/01/09 13:29:30 by diahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	do_pipe(char **av, char **env, t_pip pip)
{
	if (pipe(pip.arrf) < 0)
		put_error("Error creating pipe");
	pip.pid = fork();
	if (pip.pid < 0)
		put_error("Error forking process");
	if (!pip.pid)
		child_process(av, env, pip);
	pip.pid2 = fork();
	if (pip.pid2 < 0)
		put_error("Error forking process");
	if (!pip.pid2)
		sec_child(av, env, pip);
	close_fd(pip);
	waitpid(pip.pid, NULL, 0);
	waitpid(pip.pid2, NULL, 0);
}

int	main(int ac, char **av, char **env)
{
	t_pip	pip;

	if (ac != 5 || ((!env || !*env)))
		print_error("Error");
	pip.in_fd = open(av[1], O_RDONLY, 0644);
	if (pip.in_fd < 0)
	{
		pip.stat_in = 1;
		perror(av[1]);
	}
	else
		close(pip.in_fd);
	pip.out_fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pip.out_fd < 0)
	{
		pip.stat_out = 1;
		perror(av[4]);
	}
	else
		close(pip.out_fd);
	if (ft_strncmp(av[1], av[4], ft_strlen(av[1])) == 0 && pip.stat_in == 1)
		exit(EXIT_FAILURE);
	do_pipe(av, env, pip);
	return (0);
}
