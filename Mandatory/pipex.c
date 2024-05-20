/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:51:48 by hben-laz          #+#    #+#             */
/*   Updated: 2024/05/20 16:00:00 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(char **cmd, char **cmd_find)
{
	char	*s;
	char	*comand;
	int		i;

	i = -1;
	s = NULL;
	comand = NULL;
	s = ft_strjoin("/", cmd[0]);
	if (!s)
		return (free_t_split(cmd));
	while (cmd_find[++i])
	{
		comand = ft_strjoin(cmd_find[i], s);
		if (!comand)
			return (free(s));
		if (access(comand, X_OK) != 0)
			free(comand);
		else
			break ;
	}
	free(s);
	if (execve(comand, cmd, NULL) == -1)
		ft_error("command not found: ", cmd[0], 0, 0);
}

void	handle_file_operations(int fd_file, char **av, int *fd, int nc)
{
	if (nc == 1)
	{
		fd_file = open(av[1], O_RDONLY);
		if (fd_file == -1)
			ft_error("no such file or directory: ", av[1], 0, -1);
		dup2(fd[1], 1);
		close_fd(fd);
		dup2(fd_file, 0);
	}
	else
	{
		fd_file = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (fd_file == -1)
			ft_error("no such file or directory:", av[4], 0, 0);
		dup2(fd[0], 0);
		close_fd(fd);
		dup2(fd_file, 1);
	}
	close(fd_file);
}

void	command_1(char **av, char **env, int *fd)
{
	char	**cm1;
	char	**cmd_find;
	char	*path;

	handle_file_operations(-1, av, fd, 1);
	cm1 = ft_split(av[2], ' ');
	if (!cm1)
		ft_error("split fail :\n", "fail", 0, 0);
	if (ft_strchr(cm1[0], '/') != NULL)
	{
		if (execve(cm1[0], cm1, NULL) == -1)
			ft_error("no such file or directory: ", cm1[0], 0, 0);
	}
	path = find_path(env, "PATH=");
	if (path == NULL)
		ft_error(": no such file or directory", cm1[0], 1, 0);
	cmd_find = ft_split(path + 5, ':');
	if (!cmd_find)
	{
		free_t_split(cm1);
		ft_error("split fail :\n", "fail", 0, 0);
	}
	exec_cmd(cm1, cmd_find);
}

void	command_2(char **av, char **env, int *fd)
{
	char	**cm1;
	char	**cmd_find;
	char	*path;

	handle_file_operations(-1, av, fd, 2);
	cm1 = ft_split(av[3], ' ');
	if (!cm1)
		ft_error("split fail :\n", "fail", 0, 0);
	if (ft_strchr(cm1[0], '/') != NULL)
	{
		if (execve(cm1[0], cm1, NULL) == -1)
			ft_error("no such file or directory: ", cm1[0], 0, 0);
	}
	path = find_path(env, "PATH=");
	if (path == NULL)
		ft_error(": no such file or directory", cm1[0], 1, 0);
	cmd_find = ft_split(path, ':');
	if (!cmd_find)
	{
		free_t_split(cm1);
		ft_error("split fail :\n", "fail", 0, 0);
	}
	exec_cmd(cm1, cmd_find);
}

int	main(int ac, char **av, char **env)
{
	int	pid1;
	int	pid2;
	int	fd[2];

	if (ac != 5)
		return (write(2, "number of arg is not 5 !!\n", 27), 1);
	if (pipe(fd) == -1)
		return (perror("pipe "), 1);
	pid1 = fork();
	if (pid1 == -1)
		return (perror("pid "), close_fd(fd), 1);
	if (pid1 == 0)
		command_1(av, env, fd);
	else
	{
		pid2 = fork();
		if (pid2 == -1)
			return (perror("pid "), close_fd(fd), 1);
		if (pid2 == 0)
			command_2(av, env, fd);
	}
	close_fd(fd);
	ft_wait();
	return (0);
}
