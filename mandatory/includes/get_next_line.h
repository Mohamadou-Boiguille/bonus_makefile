/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:34:58 by moboigui          #+#    #+#             */
/*   Updated: 2023/09/10 19:01:03 by hamzaelouar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX FOPEN_MAX
# endif

# include "cub3d.h"

void				memmove_at_start(char *buff, int len);
char				*my_strjoin(char *to_add, char *buff, int nb_of_char);
char				*ft_realloc(char *to_add, char *buff, int nb_of_char);
int					check_nl(int nb_of_char, char *buff, char *line);
char				*get_next_line(int fd);

#endif
