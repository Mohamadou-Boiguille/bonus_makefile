/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboigui <moboigui@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:21:41 by moboigui          #+#    #+#             */
/*   Updated: 2022/11/13 20:21:43 by moboigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_bzero(void *s, int n)
{
	char	*src;
	int		i;

	i = 0;
	src = s;
	while (i < n)
		src[i++] = '\0';
	return (s);
}
