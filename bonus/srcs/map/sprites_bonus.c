/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:18:09 by hamzaelouar       #+#    #+#             */
/*   Updated: 2023/09/10 12:43:41 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_sprites(t_infos *vars, t_ray *ray)
{
	int	i;
	int	x;
	int	y;
	int	color;

	i = 0;
	while (i < vars->map->sprite_count)
	{
		x = vars->map->sprites[i]->x;
		y = vars->map->sprites[i]->y;
		if (ray->map_x == x && ray->map_y == y)
		{
			color = 0x00FF00;
			*(int *)(vars->display->data + ray->draw_start * PXL_LINE
					+ ray->column * 4) = color;
		}
		i++;
	}
}
