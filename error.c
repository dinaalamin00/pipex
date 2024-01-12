/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diahmed <diahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:13:30 by diahmed           #+#    #+#             */
/*   Updated: 2024/01/09 13:05:10 by diahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	put_error(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

void	print_error(char *s)
{
	ft_putendl_fd(s, 2);
	exit(EXIT_FAILURE);
}

void	cmd_err(char *cmdstr, char *errmsg)
{
	ft_putstr_fd(cmdstr, 2);
	print_error(errmsg);
}

char	**ft_free(char **ptr)
{
	size_t	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
	return (NULL);
}

void	close_fd(t_pip pip)
{
	if (pip.arrf[0] != -1 && pip.arrf[0] > 2)
		close(pip.arrf[0]);
	if (pip.arrf[1] != -1 && pip.arrf[1] > 2)
		close(pip.arrf[1]);
	if (pip.in_fd != -1 && pip.in_fd > 2)
		close(pip.in_fd);
	if (pip.out_fd != -1 && pip.out_fd > 2)
		close(pip.out_fd);
	close(0);
	close(1);
	close(2);
}
