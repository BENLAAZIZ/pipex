/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:51:48 by hben-laz          #+#    #+#             */
/*   Updated: 2024/05/19 23:14:09 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_command(t_data *data, int i)
{
	char	**cm1;

	handle_file_operations(data, 1);
	cm1 = ft_split(data->av[i], ' ');
	if (!cm1)
		ft_error("split fail :\n", "fail", 0);
	if (ft_strchr(cm1[0], '/') != NULL)
	{
		if (execve(cm1[0], cm1, NULL) == -1)
		{
			ft_error("no such file or directory: ", cm1[0], 0);
			exit(1);
		}
	}
	if (data->path == NULL)
	{
		ft_error(": no such file or directory", cm1[0], 1);
		free_t_split(cm1);
		exit(1);
	}
	exec_cmd(cm1, data->path);
}

void	last_command(t_data *data)
{
	char	**cm1;

	handle_file_operations(data, 2);
	cm1 = ft_split(data->av[data->ac - 2], ' ');
	if (!cm1)
		ft_error("split fail :\n", "fail", 0);
	if (ft_strchr(cm1[0], '/') != NULL)
	{
		if (execve(cm1[0], cm1, NULL) == -1)
		{
			ft_error("no such file or directory: ", cm1[0], 0);
			exit(1);
		}
	}
	if (data->path == NULL)
	{
		ft_error(": no such file or directory", cm1[0], 1);
		free_t_split(cm1);
		exit(1);
	}
	exec_cmd(cm1, data->path);
}

void	intermediat(char *str, t_data *data)
{
	char	**cm1;

	if (dup2(data->fd[1], 1) == -1)
		ft_error("dup2 fail : \n", "fail", 0);
	close_fd(data->fd);
	cm1 = ft_split(str, ' ');
	if (!cm1)
		ft_error("split fail :\n", "fail", 0);
	if (ft_strchr(cm1[0], '/') != NULL)
	{
		if (execve(cm1[0], cm1, NULL) == -1)
		{
			ft_error("no such file or directory: ", cm1[0], 0);
			exit(1);
		}
	}
	if (data->path == NULL)
	{
		ft_error(": no such file or directory", cm1[0], 1);
		free_t_split(cm1);
		exit(1);
	}
	exec_cmd(cm1, data->path);
}

int	al_command(t_data *data, int i)
{
	int	pid;

	while (++i < data->ac - 3)
	{
		if (pipe(data->fd) == -1)
			return (perror("pipe fail :"), 1);
		pid = fork();
		if (pid == -1)
			return (perror("pid fail :"), close_fd(data->fd), 1);
		else if (pid == 0 && i == 0)
			first_command(data, i + 2);
		else if (pid == 0 && i == data->ac - 4)
		{
			last_command(data);
			break ;
		}
		else if (pid == 0)
			intermediat(data->av[i + 2], data);
		if (dup2(data->fd[0], 0) == -1)
			ft_error("dup2 fail : \n", "fail", 0);
		close_fd(data->fd);
	}
	close_fd(data->fd);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	int		i;

	i = -1;
	ft_initialis_data(&data, ac, av, env);
	if (ac < 5)
		return (write(2, "min 5 arg", 9), 1);
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		here_doc(av[2], ac, data.fd);
		i += 1;
	}
	if (al_command(&data, i) == 1)
		return (1);
	close(0);
	wait_function(ac);
	return (0);
}
