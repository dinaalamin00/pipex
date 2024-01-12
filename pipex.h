/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diahmed <diahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:10:11 by diahmed           #+#    #+#             */
/*   Updated: 2024/01/09 13:31:21 by diahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include "libft/libft.h"

typedef struct s_pip
{
	int		i;
	char	*path;
	char	**cmd;
	char	**cmd_path;
	char	*tmp;
	int		in_fd;
	int		out_fd;
	int		stat_in;
	int		stat_out;
	int		arrf[2];
	pid_t	pid;
	pid_t	pid2;
}	t_pip;

void	child_process(char **av, char **env, t_pip pip);
void	sec_child(char **av, char **env, t_pip pip);
void	exec_cmd(char *cmdstr, t_pip pip, char **env);
void	put_error(char *s);
void	print_error(char *s);
void	cmd_err(char *cmdstr, char *errmsg);
char	**ft_free(char **ptr);
void	close_fd(t_pip pip);

#endif