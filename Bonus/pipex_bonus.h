/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:52:09 by hben-laz          #+#    #+#             */
/*   Updated: 2024/05/19 19:31:37 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/_types.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

typedef struct s_data
{
	char	*path;
	char	**av;
	int		fd[2];
	int		ac;
	int		fd_file;
}	t_data;

size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_error(char *s, char *flag, int i);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
void	*ft_memcpy(void	*dst, const void *src, size_t n);
void	free_t_split(char **array);
void	close_fd(int *fd);
void	wait_function(int ac);
char	*ft_strchr(const char *s, int c);
char	*find_path(char **env, char *str);
void	exec_cmd(char **cmd, char **cmd_find);
void	handle_file_operations(t_data *data, int nc);
void	here_doc(char *limiter, int ac, int *fd);
void	ft_initialis_data(t_data *data, int ac, char **av, char **env);

#endif
