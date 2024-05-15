/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:50:04 by hben-laz          #+#    #+#             */
/*   Updated: 2024/05/15 23:34:51 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if ((unsigned char)c == '\0')
		return ((char *)s + ft_strlen(s));
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}


void	ft_error(char *s)
{
	write(2, s, ft_strlen(s));
	exit(1);
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
