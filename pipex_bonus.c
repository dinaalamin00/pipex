/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diahmed <diahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:33:25 by diahmed           #+#    #+#             */
/*   Updated: 2024/01/09 10:42:53 by diahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	print_error_b(char *s)
{
	ft_putendl_fd(s, 2);
	exit(EXIT_FAILURE);
}

static void	get_nl(char **av, int *pfd)
{
	char	*line;

	close (pfd[0]);
	while (1)
	{
		line = get_next_line(0);
		if (ft_strncmp(line, av[2], ft_strlen(av[2])) == 0)
		{
			close(pfd[1]);
			free(line);
			exit(0);
		}
		ft_putstr_fd(line, pfd[1]);
		free(line);
	}
}

void	put_in_file(char **av)
{
	int		pfd[2];
	pid_t	pid;

	if (pipe(pfd) < 0)
		put_error_b("Error creating pipe");
	pid = fork();
	if (pid < 0)
		put_error_b("Error forking process");
	if (!pid)
	{
		get_nl(av, pfd);
	}
	else
	{
		close (pfd[1]);
		if (dup2(pfd[0], STDIN_FILENO) < 0)
			put_error_b("Error duplicating file descriptor");
		close(pfd[0]);
		waitpid(pid, NULL, 0);
	}
}

void	do_pip(int ac, char **av, t_pip_b pip, char **env)
{
	while (pip.i < ac - 2)
		exec_cmd(av[pip.i++], pip, env);
	pip.out_fd = open_fd(av[ac - 1], pip, 1);
	if (dup2(pip.out_fd, 1) < 0)
		put_error_b("Error duplicating file descriptor");
	close(pip.out_fd);
	exec_cmd_b(av[ac - 2], pip, env);
}
