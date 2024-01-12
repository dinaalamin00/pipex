/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diahmed <diahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 09:27:19 by diahmed           #+#    #+#             */
/*   Updated: 2024/01/12 13:03:06 by diahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_mem(t_pip pip, char *cmdstr, char *errmsg)
{
	ft_putstr_fd(cmdstr, 2);
	ft_putendl_fd(errmsg, 2);
	if (pip.cmd != NULL && *pip.cmd != NULL)
		ft_free(pip.cmd);
	if (pip.cmd_path != NULL && *pip.cmd_path != NULL)
		ft_free(pip.cmd_path);
	close_fd(pip);
	exit(EXIT_FAILURE);
}

static char	**get_path(char **cmd, char **env)
{
	int		i;
	char	**cmdpath;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			cmdpath = ft_split(env[i] + 5, ':');
			if (!cmdpath)
			{
				ft_free(cmd);
				put_error("path error");
			}
			return (cmdpath);
		}
		i++;
	}
	return (NULL);
}

void	exec_cmd(char *cmdstr, t_pip pip, char **env)
{
	pip.i = 0;
	pip.cmd = ft_split(cmdstr, 32);
	if (!pip.cmd || !(*pip.cmd))
	{
		ft_free(pip.cmd);
		print_error("invalid command");
	}
	pip.cmd_path = get_path(pip.cmd, env);
	if (!pip.cmd_path)
		cmd_err(*pip.cmd, ": No such file or directory");
	while (pip.cmd_path && pip.cmd_path[pip.i])
	{
		pip.tmp = ft_strjoin(pip.cmd_path[pip.i], "/");
		pip.path = ft_strjoin(pip.tmp, pip.cmd[0]);
		free(pip.tmp);
		if (!access(pip.path, (F_OK | X_OK)))
			break ;
		free(pip.path);
		(pip.i)++;
	}
	if (!pip.cmd_path[pip.i])
		free_mem(pip, pip.cmd[0], ": command not found");
	if (execve(pip.path, pip.cmd, env) < 0)
		free_mem(pip, pip.cmd[0], ": command not found");
}

void	child_process(char **av, char **env, t_pip pip)
{
	close(pip.arrf[0]);
	pip.in_fd = open(av[1], O_RDONLY);
	if (pip.in_fd < 0)
	{
		if (pip.stat_in != 1)
			put_error(av[1]);
		else
		{
			close(pip.arrf[1]);
			exit(EXIT_FAILURE);
		}
	}
	if (dup2(pip.in_fd, STDIN_FILENO) < 0)
		put_error("Error duplicating file descriptor");
	close(pip.in_fd);
	if (dup2(pip.arrf[1], STDOUT_FILENO) < 0)
		put_error("Error duplicating file descriptor");
	close(pip.arrf[1]);
	exec_cmd(av[2], pip, env);
}

void	sec_child(char **av, char **env, t_pip pip)
{
	pip.out_fd = open(av[4], O_WRONLY | O_TRUNC, 0644);
	if (pip.out_fd < 0)
	{
		if (pip.stat_out != 1)
			put_error(av[4]);
		else
		{
			close(pip.arrf[0]);
			close(pip.arrf[1]);
			exit(EXIT_FAILURE);
		}
	}
	close (pip.arrf[1]);
	if (dup2(pip.arrf[0], STDIN_FILENO) < 0)
		put_error("Error duplicating file descriptor");
	close(pip.arrf[0]);
	if (dup2(pip.out_fd, STDOUT_FILENO) < 0)
		put_error("Error duplicating file descriptor");
	close(pip.out_fd);
	exec_cmd(av[3], pip, env);
}
