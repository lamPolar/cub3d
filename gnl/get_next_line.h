/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:18:37 by heeskim           #+#    #+#             */
/*   Updated: 2022/09/03 03:11:50 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 50
# include <stdlib.h>
# include <unistd.h>

//get_next_line.c
int		gnl_isnl(char *s);
char	*get_next_line(int fd);
char	*gnl_readline(int fd, char **saved);
char	*gnl_makeresult(int fd, char	**saved);
char	*gnl_free(char **saved, char *buf);

//get_next_line_utils.c
char	*gnl_strjoin(char *saved, char *buf);
char	*gnl_strcut(char const *saved, int nl);
void	gnl_strcpy(char *dst, const char *src, int len);
void	gnl_strmove(char *saved, int len);
void	*gnl_calloc(size_t count, size_t size);

#endif
