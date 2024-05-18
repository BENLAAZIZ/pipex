/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:51:48 by hben-laz          #+#    #+#             */
/*   Updated: 2024/05/18 23:43:57 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_command(char **av, char **env, int *fd, int i)
{
	char	**cm1;
	char	**cmd_find;
	char	*path;

	handle_file_operations(av, 0, fd, 1);
	cm1 = ft_split(av[i], ' ');
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
	char	*path;

	handle_file_operations(av, ac, fd, 2);
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
		ft_error(" intermid dup2 fail : \n", "fail", 0);
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

int	al_command(int ac, char **av, char **env, int i, int *fd)
{
	int	pid;

	while (i < ac - 3)
	{
		if (pipe(fd) == -1)
			return (perror("pipe fail :"), 1);
		pid = fork();
		if (pid == -1)
			return (perror("pid fail :"), close_fd(fd), 1);
		else if (pid == 0 && i == 0)
			first_command(av, env, fd, i);
		else if (pid == 0 && i == ac - 4)
		{
			last_command(av, env, fd, ac);
			break ;
		}
		else if (pid == 0)
			intermediat(av[i], env, fd);
		if (dup2(fd[0], 0) == -1)
			ft_error("dup2 fail : \n", "fail", 0);
		close_fd(fd);
		i++;
	}
	close_fd(fd);
	return (0);
}


void	here_doc(char *limiter, int ac, int *fd)
{
	char	*line;

	if (ac < 6)
		ft_error("min 6 arg : \n", "fail", 0);
	fd[1] = open("herd.txt", O_RDWR | O_CREAT | O_APPEND, 0777); // addad
	fd[0] = open("herd.txt", O_RDWR | O_CREAT | O_APPEND, 0777);
	if (fd[1] == -1 || fd[0] == -1)
		ft_error("open fail : \n", "fail", 0);
	unlink("herd.txt");
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& ft_strlen(limiter) == ft_strlen(line) - 1)
			break ;
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	if (dup2(fd[0], 0) == -1)
		ft_error("dup2 : ", "fail", 0);
}

// i = 0;

// i < ac - 3
int	main(int ac, char **av, char **env)
{
	int	i;
	int fd[2];

	i = 0;
	if (ac < 5)
		return (write(2, "min 5 arg", 9), 1);
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		here_doc(av[2] , ac, fd);
		i += 2;
	}
	if (al_command(ac, av, env, i, fd) == 1)
		return (1);
	close(0);
	wait_function(ac);
	return (0);
}
