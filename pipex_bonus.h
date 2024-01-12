/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diahmed <diahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 12:19:51 by diahmed           #+#    #+#             */
/*   Updated: 2024/01/09 13:31:27 by diahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include "get_next_line.h"

typedef struct s_pip_b
{
	int		i;
	int		j;
	int		pfd[2];
	pid_t	pid;
	int		in_fd;
	int		out_fd;
	int		stat_in;
	int		stat_out;
	char	*path;
	char	**cmd;
	char	**cmd_path;
	char	*tmp;
}	t_pip_b;

int		open_fd(char *fname, t_pip_b pip, int mode);
void	put_in_file(char **av);
void	do_pip(int ac, char **av, t_pip_b pip, char **env);
void	exec_cmd(char *cmd, t_pip_b pip, char **env);
void	exec_cmd_b(char *cmdstr, t_pip_b pip, char **env);
char	*get_next_line(int fd);
void	print_error_b(char *s);
void	put_error_b(char *s);
void	close_fd_b(void);
char	**ft_free(char **ptr);

#endif