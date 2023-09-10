/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:15:13 by hamzaelouar       #+#    #+#             */
/*   Updated: 2023/09/10 12:15:13 by hamzaelouar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(const char *str, const char *charset)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (ft_strchr(charset, *str))
		{
			if (in_word)
				in_word = 0;
		}
		else
		{
			if (!in_word)
			{
				count++;
				in_word = 1;
			}
		}
		str++;
	}
	return (count);
}

int	word_length(const char *str, const char *charset)
{
	int	length;

	length = 0;
	while (*str && !ft_strchr(charset, *str))
	{
		length++;
		str++;
	}
	return (length);
}

void	*secure_malloc(char **words, int i)
{
	while (i--)
		free(words[i]);
	free(words);
	return (NULL);
}

char	**ft_set_split(char *str, char *charset)
{
	int		nb_words;
	char	**words;
	int		i;
	int		len;

	nb_words = count_words(str, charset);
	words = ft_calloc((nb_words + 1), sizeof(char *));
	if (!words)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (ft_strchr(charset, *str))
			str++;
		else
		{
			len = word_length(str, charset);
			words[i] = malloc((len + 1) * sizeof(char));
			if (!words[i])
				return (secure_malloc(words, i));
			str += ft_strlcpy(words[i++], str, len);
		}
	}
	return (words);
}
