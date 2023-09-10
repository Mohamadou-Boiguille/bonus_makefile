/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:57:56 by moboigui          #+#    #+#             */
/*   Updated: 2023/09/10 19:02:57 by hamzaelouar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_floor_and_ceiling(t_infos *vars, t_ray *ray, int start, int end)
{
	int	y;
	int	color;

	y = -1;
	while (++y < RES_H)
	{
		if (y == start || (y > start && y < end))
			y = end;
		if (y < start && y < RES_HALF_HEIGHT)
		{
			color = vars->map->ceiling->color_nb;
		}
		else if (y >= end && y > RES_HALF_HEIGHT)
			color = vars->map->floor->color_nb;
		*(int *)(vars->display->data + y * PXL_LINE + ray->column * 4) = color;
	}
}

void	draw_vertical_line(t_infos *vars, t_ray *ray)
{
	t_img	*text;
	int		y;
	int		d;
	int		color;

	y = ray->draw_start - 1;
	text = ray->tex;
	while (++y < ray->draw_end)
	{
		d = y * 256 - HEIGHTX128 + ray->line_height * 128;
		ray->tex_y = (d * text->height) / (ray->line_height * 256);
		if (ray->tex_y < 0)
			ray->tex_y = 0;
		color = get_pixel_value(text, ray->tex_x, ray->tex_y);
		*(int *)(vars->display->data + y * PXL_LINE + ray->column * 4) = color;
	}
	draw_floor_and_ceiling(vars, ray, ray->draw_start, ray->draw_end);
}
