/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:51:48 by hben-laz          #+#    #+#             */
/*   Updated: 2024/05/16 19:41:57 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*find_path(char **env, char *str)
{
	int	i;

	i = 0;
	if (!env || !env[0] || !str)
		return (NULL);
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
		ft_error("command not found: ", cmd[0], 0);
}

void	first_command(char **av, char **env, int *fd, int i)
{
	char	**cm1;
	char	**cmd_find;
	int		fd_in;
	char	*path;

	fd_in = open(av[1], O_RDONLY);
	if (fd_in == -1)
		ft_error("file fail :\n", "fail", 0);
	if (dup2(fd[1], 1) == -1)
		ft_error("dup2 fail :\n", "fail", 0);
	close_fd(fd);
	if (dup2(fd_in, 0) == -1)
		ft_error("dup2 fail :\n", "fail", 0);
	close(fd_in);
	cm1 = ft_split(av[i + 2], ' ');
	if (!cm1)
		ft_error("split fail :\n", "fail", 0);
	if (ft_strchr(cm1[0], '/') != NULL)
	{
		if (execve(cm1[0], cm1, NULL) == -1)
			ft_error("no such file or directory: ", cm1[0], 0);
	}
	path = find_path(env, "PATH=");
	if (path == NULL)
		ft_error(": no such file or directory", cm1[0], 1);
	cmd_find = ft_split(path, ':');
	if (!cmd_find)
	{
		free_t_split(cm1);
		ft_error("split fail :\n", "fail", 0);
	}
	exec_cmd(cm1, cmd_find);
}

void	last_command(char **av, char **env, int *fd, int ac)
{
	char	**cm1;
	char	**cmd_find;
	int		fd_out;
	char	*path;

	close_fd(fd);
	fd_out = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
		ft_error("file fail :\n", "fail", 0);
	if (dup2(fd_out, 1) == -1)
		ft_error("dup2 fail :\n", "fail", 0);
	close(fd_out);
	cm1 = ft_split(av[ac - 2], ' ');
	if (!cm1)
		ft_error("split fail :\n", "fail", 0);
	if (ft_strchr(cm1[0], '/') != NULL)
	{
		if (execve(cm1[0], cm1, NULL) == -1)
			ft_error("no such file or directory: ", cm1[0], 0);
		
	}
	path = find_path(env, "PATH=");
	if (path == NULL)
		ft_error(": no such file or directory", cm1[0], 1);
	cmd_find = ft_split(path, ':');
	if (!cmd_find)
	{
		free_t_split(cm1);
		ft_error("split fail :\n", "fail", 0);
	}
	exec_cmd(cm1, cmd_find);
}

void	intermediat(char *av,char **env, int *fd)
{
	char	**cm1;
	char	**cmd_find;
	char	*path;

	if (dup2(fd[1], 1) == -1)
		ft_error("dup2 fail : \n", "fail", 0);
	close_fd(fd);
	cm1 = ft_split(av, ' ');
	if (!cm1)
		ft_error("split fail :\n", "fail", 0);
	if (ft_strchr(cm1[0], '/') != NULL)
	{
		execve(cm1[0], cm1, NULL);
			ft_error("no such file or directory: ", cm1[0], 0);
	}
	path = find_path(env, "PATH=") + 5;
	if (!path)
		ft_error(": no such file or directory", cm1[0], 1);
	cmd_find = ft_split(path, ':');
	if (!cmd_find)
	{
		free_t_split(cm1);
		ft_error("split fail :\n", "fail", 0);
	}
	exec_cmd(cm1, cmd_find);
}

int	al_command(int ac, char **av,char **env,int i)
{
	int	pid;
	int	fd[2];

	while (++i < ac - 3)
	{
		if (pipe(fd) == -1)
			return (perror("pipe fail :"), 1);
		pid = fork();
		if (pid == -1)
			return (perror("pid fail :"), close_fd(fd), 1);
		if (pid == 0 && i == 0)
			first_command(av, env, fd, i);
		if (pid == 0 && i == ac - 4)
		{
			last_command(av, env, fd, ac);
			break ;
		}
		else if (pid == 0)
			intermediat(av[i + 2], env, fd);
		dup2(fd[0], 0);
		close_fd(fd);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	if (ac < 5)
		return (write(2, "min 5 arg", 9), 1);
	if (al_command(ac, av, env, -1) == 1)
		return (1);
	close(0);
	wait_function(ac);
	return (0);
}
