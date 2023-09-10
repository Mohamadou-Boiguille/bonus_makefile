/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specific_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:18:29 by hamzaelouar       #+#    #+#             */
/*   Updated: 2023/09/10 13:07:15 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_delim(char c, char *delims)
{
	while (*delims)
	{
		if (c == *delims)
			return (1);
		delims++;
	}
	return (0);
}

int	count_words(char *str, char *delims)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (is_delim(*str, delims))
			str++;
		if (*str)
		{
			count++;
			while (*str && !is_delim(*str, delims))
				str++;
		}
	}
	return (count);
}

char	*alloc_word(char *str, char *delims, t_infos *vars)
{
	int		i;
	int		len;
	char	*word;

	i = -1;
	len = 0;
	while (str[len] && !is_delim(str[len], delims))
		len++;
	word = garb_col_mlx(vars, ALLOC, sizeof(char) * (len + 1), NULL);
	if (!word)
		return (NULL);
	while (++i < len)
		word[i] = str[i];
	word[len] = '\0';
	return (word);
}

char	**ft_specific_split(char *str, char *delims, t_infos *vars)
{
	int		n_words;
	char	**words;
	int		i;

	n_words = count_words(str, delims);
	words = garb_col_mlx(vars, ALLOC, sizeof(char *) * (n_words + 1), NULL);
	if (!words)
		return (NULL);
	i = 0;
	while (*str)
	{
		while (is_delim(*str, delims))
			str++;
		if (*str)
		{
			words[i++] = alloc_word(str, delims, vars);
			if (!words[i - 1])
				return (NULL);
			while (*str && !is_delim(*str, delims))
				str++;
		}
	}
	words[i] = NULL;
	return (words);
}

void	free_split(char **array)
{
	int	i;

	i = 0;
	while (array[i] == NULL)
		free(array[i++]);
	free(array);
}
