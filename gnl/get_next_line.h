/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 16:34:51 by zcolleen          #+#    #+#             */
/*   Updated: 2020/07/23 16:37:01 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# define BUFFER_SIZE 120

# include <unistd.h>
# include <stdlib.h>

int		get_next_line(int fd, char **line);
int		loc(char *buffer, char **line, char **s);
int		copy(char *tmp, char **line);
char	*search_for_n(char *buffer);
char	*s_save(char *pointer, char *s);
int		fr(char *p, char **s);
int		concatination(char **line, char **s);
int		line_copy(char **line, char *s);

#endif
