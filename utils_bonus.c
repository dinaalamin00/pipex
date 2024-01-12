/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diahmed <diahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:16:12 by diahmed           #+#    #+#             */
/*   Updated: 2024/01/12 13:04:29 by diahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	cmd_err_b(char *cmdstr, char *errmsg)
{
	ft_putstr_fd(cmdstr, 2);
	print_error_b(errmsg);
}

static void	free_mem_b(t_pip_b pip, char *cmdstr, char *errmsg)
{
	ft_putstr_fd(cmdstr, 2);
	ft_putendl_fd(errmsg, 2);
	if (pip.cmd != NULL && *pip.cmd != NULL)
		ft_free(pip.cmd);
	if (pip.cmd_path != NULL && *pip.cmd_path != NULL)
		ft_free(pip.cmd_path);
	close_fd_b();
	exit(EXIT_FAILURE);
}

char	**get_path_b(char **cmd, char **env)
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
				put_error_b("path error");
				break ;
			}
			return (cmdpath);
		}
		i++;
	}
	return (NULL);
}

void	exec_cmd_b(char *cmdstr, t_pip_b pip, char **env)
{
	pip.j = 0;
	pip.cmd = ft_split(cmdstr, 32);
	if (!pip.cmd || !(*pip.cmd))
	{
		ft_free(pip.cmd);
		put_error_b("invalid command");
	}
	pip.cmd_path = get_path_b(pip.cmd, env);
	if (!pip.cmd_path)
		cmd_err_b(*pip.cmd, ": No such file or directory");
	while (pip.cmd_path[pip.j])
	{
		pip.tmp = ft_strjoin(pip.cmd_path[pip.j], "/");
		pip.path = ft_strjoin(pip.tmp, pip.cmd[0]);
		free(pip.tmp);
		if (!access(pip.path, (F_OK | X_OK)))
			break ;
		free(pip.path);
		(pip.j)++;
	}
	if (!pip.cmd_path[pip.j] || !pip.cmd_path)
		free_mem_b(pip, *pip.cmd, ": command not found");
	if (execve(pip.path, pip.cmd, env) < 0)
		free_mem_b(pip, *pip.cmd, ": command not found");
}

void	exec_cmd(char *cmd, t_pip_b pip, char **env)
{
	if (pipe(pip.pfd) < 0)
		put_error_b("Error creating pipe");
	pip.pid = fork();
	if (pip.pid < 0)
		put_error_b("Error forking process");
	if (!pip.pid)
	{
		close (pip.pfd[0]);
		if (dup2(pip.pfd[1], 1) < 0)
			put_error_b("Error duplicating file descriptor");
		close(pip.pfd[1]);
		exec_cmd_b(cmd, pip, env);
	}
	else
	{
		close (pip.pfd[1]);
		if (dup2(pip.pfd[0], 0) < 0)
			put_error_b("Error duplicating file descriptor");
		close(pip.pfd[0]);
		waitpid(pip.pid, NULL, 0);
	}
}
