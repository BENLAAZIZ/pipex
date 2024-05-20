/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:52:09 by hben-laz          #+#    #+#             */
/*   Updated: 2024/05/20 01:39:34 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/_types.h>

size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_error(char *s, char *flag, int i, int in);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
void	*ft_memcpy(void	*dst, const void *src, size_t n);
void	free_t_split(char **array);
void	close_fd(int *fd);
void	ft_wait(void);
char	*ft_strchr(const char *s, int c);
char	*find_path(char **env, char *str);

#endif	