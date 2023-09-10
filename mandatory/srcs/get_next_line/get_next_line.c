/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:08:50 by moboigui          #+#    #+#             */
/*   Updated: 2023/09/10 19:02:48 by hamzaelouar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

char	*ft_specificjoin(char *s1, char *s2)
{
	char	*result;
	ssize_t	len;
	size_t	index;

	len = ft_strlen(s1) + ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	index = 0;
	while (s1 && s1[index])
	{
		result[index] = s1[index];
		index++;
	}
	len = -1;
	while (s2 && s2[++len])
		result[index + len] = s2[len];
	result[index + len] = '\0';
	if (s1)
		free(s1);
	return (result);
}

char	*ft_readfile(int fd, char *backup)
{
	int		read_buf;
	char	*result_line;

	read_buf = 1;
	result_line = NULL;
	if (backup[0])
		result_line = ft_specificjoin(result_line, backup);
	while (ft_strichr(backup, '\n') == -1 && read_buf > 0)
	{
		read_buf = read(fd, backup, BUFFER_SIZE);
		if (read_buf < 0)
			return (NULL);
		backup[read_buf] = '\0';
		result_line = ft_specificjoin(result_line, backup);
		if (!result_line)
			return (NULL);
	}
	return (result_line);
}

void	ft_backupfill(char *line, char *backup, size_t start)
{
	ssize_t	index;

	index = -1;
	while (line[start + ++index])
		backup[index] = line[start + index];
	backup[index] = '\0';
}

char	*ft_getline(char *line, char *backup)
{
	char	*final_line;
	ssize_t	index;

	index = -1;
	if (line[0] == '\0')
		return (free(line), NULL);
	while (line[++index] && line[index] != '\n')
		;
	final_line = (char *)malloc(sizeof(char) * (index + 2));
	if (!final_line)
		return (NULL);
	index = -1;
	while (line[++index] && line[index] != '\n')
		final_line[index] = line[index];
	final_line[index] = line[index];
	final_line[index + 1] = '\0';
	if (line[index++] != '\0')
		ft_backupfill(line, backup, index);
	free(line);
	return (final_line);
}

char	*get_next_line(int fd)
{
	static char	backup[BUFFER_SIZE + 1];
	char		*line_read;

	line_read = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line_read = ft_readfile(fd, backup);
	if (!line_read)
		return (NULL);
	return (ft_getline(line_read, backup));
}
