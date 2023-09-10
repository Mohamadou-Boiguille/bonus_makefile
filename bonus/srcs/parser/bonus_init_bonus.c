/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 13:09:01 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/09/10 13:48:18 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	**load_sprites(t_infos *vars)
{
	int		i;
	char	sprites_name[] = "./textures/balancing1.xpm";
	void	**sprites_array;

	i = 0;
	sprites_array = garb_col_mlx(vars, ALLOC, 8 * sizeof(void *), NULL);
	while (i < 8)
	{
		write(1, "|\n", 2);
		sprites_array[i] = garb_col_mlx(vars, TEXTURE, 0, sprites_name);
		sprites_name[20] += 1;
		i++;
	}
	return (sprites_array);
}
