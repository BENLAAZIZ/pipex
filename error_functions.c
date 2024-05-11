/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:50:04 by hben-laz          #+#    #+#             */
/*   Updated: 2024/05/11 23:41:15 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *s)
{
	if (ft_strncmp(s, "dup2", 4) == 0)
		perror("dup2 fail :");
	else if (ft_strncmp(s, "split", 5) == 0)
		perror("split fail :");
	else if (ft_strncmp(s, "file", 4) == 0)
		perror("file fail :");
	else
		perror("Error :");
	exit(0);
}

void	free_t_split(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	close_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	ft_wait(void)
{
	int	i;

	i = 2;
	while (i--)
	{
		if (wait(NULL) == -1)
			return ;
	}
}
