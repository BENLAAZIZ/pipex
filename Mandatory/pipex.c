/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:51:48 by hben-laz          #+#    #+#             */
/*   Updated: 2024/05/15 23:46:27 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **env, char *str)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, ft_strlen(str)) == 0)
			return (env[i]);
		i++;
	}
	return (NULL);
}

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
		ft_error("command not found: \n");
}

void	command_1(char **av, char **env, int *fd)
{
	char	**cm1;
	char	**cmd_find;
	int		fd_in;

	fd_in = open(av[1], O_RDONLY);
	if (fd_in == -1)
		ft_error("file fail :\n");
	if (dup2(fd[1], 1) == -1)
		ft_error("dup2 fail :\n");
	close_fd(fd);
	if (dup2(fd_in, 0) == -1)
		ft_error("dup2 fail :\n");
	close(fd_in);
	cm1 = ft_split(av[2], ' ');
	if (!cm1)
		ft_error("split fail :\n");
	if (ft_strchr(cm1[0], '/') != NULL)
	{
		if (execve(cm1[0], cm1, NULL) == -1)
			ft_error("command not found:\n");
	}
	cmd_find = ft_split(find_path(env, "PATH=") + 5, ':');
	if (!cmd_find)
	{
		free_t_split(cm1);
		ft_error("split fail :\n");
	}
	exec_cmd(cm1, cmd_find);
}

void	command_2(char **av, char **env, int *fd)
{
	char	**cm1;
	char	**cmd_find;
	int		fd_out;

	fd_out = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
		ft_error("file fail :\n");
	if (dup2(fd[0], 0) == -1)
		ft_error("dup2 fail :\n");
	close_fd(fd);
	if (dup2(fd_out, 1) == -1)
		ft_error("dup2 fail :\n");
	close(fd_out);
	cm1 = ft_split(av[3], ' ');
	if (!cm1)
		ft_error("split fail :\n");
	if (ft_strchr(cm1[0], '/') != NULL)
	{
		if (execve(cm1[0], cm1, NULL) == -1)
			ft_error("command not found:\n");
	}
	cmd_find = ft_split(find_path(env, "PATH=") + 5, ':');
	if (!cmd_find)
	{
		free_t_split(cm1);
		ft_error("split fail :\n");
	}
	exec_cmd(cm1, cmd_find);
}

int	main(int ac, char **av, char **env)
{
	int	pid1;
	int	pid2;
	int	fd[2];

	if (ac != 5)
		return (perror("arg fail : \n"), 1);
	if (pipe(fd) == -1)
		return (perror("pipe fail : \n"), 1);
	pid1 = fork();
	if (pid1 == -1)
		return (perror("pid fail : \n"), close_fd(fd), 1);
	if (pid1 == 0)
		command_1(av, env, fd);
	else
	{
		pid2 = fork();
		if (pid2 == -1)
			return (perror("pid fail : \n"), close_fd(fd), 1);
		if (pid2 == 0)
			command_2(av, env, fd);
	}
	close_fd(fd);
	ft_wait();
	return (0);
}
