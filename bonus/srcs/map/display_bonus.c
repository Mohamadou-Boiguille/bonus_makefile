/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:17:40 by hamzaelouar       #+#    #+#             */
/*   Updated: 2023/09/10 13:51:29 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <stdio.h>

void	draw_player_point(t_infos *vars)
{
	int	i;
	int	j;
	int	pixel;

	i = 0;
	while (i < 6)
	{
		j = 0;
		while (j < 6)
		{
			pixel = ((47 + i) * PXL_LINE) + ((47 + j) * 4);
			*(int *)(vars->display->data + pixel) = 0xFF0000;
			j++;
		}
		i++;
	}
}

void	minimap_to_img(t_infos *vars, t_minimap *minimap)
{
	t_map	*map;
	int		color;
	int		x;
	int		y;

	map = vars->map;
	x = (minimap->x + minimap->x_offset) / 10;
	y = (minimap->y + minimap->y_offset) / 10;
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
		color = 0x555555;
	else if (map->grid[y][x] == '0')
		color = 0xAAAAAA;
	else if (map->grid[y][x] == '1')
		color = 0xFFFFFF;
	else
		color = 0x555555;
	*(int *)(vars->display->data + minimap->position) = color;
}

void	draw_minimap(t_infos *vars)
{
	int			i;
	int			j;
	t_minimap	minimap;

	i = 0;
	minimap.x_offset = vars->player->x * 10 - 50;
	minimap.y_offset = vars->player->y * 10 - 50;
	while (i <= MINIMAP_SIZE)
	{
		j = 0;
		while (j <= MINIMAP_SIZE)
		{
			minimap.y = i;
			minimap.x = j;
			minimap.position = (i * vars->width + j) * 4;
			minimap_to_img(vars, &minimap);
			j++;
		}
		i++;
	}
	draw_player_point(vars);
}

void	draw_floor_and_ceiling(t_infos *vars, t_ray *ray, int start, int end)
{
	int	y;

	y = -1;
	if (ray->column <= MINIMAP_SIZE && y <= MINIMAP_SIZE)
		y = MINIMAP_SIZE;
	while (++y < RES_H)
	{
		if (y == start || (y > start && y < end))
			y = end;
		*(int *)(vars->display->data + y * PXL_LINE + ray->column * 4) \
			= vars->map->b_g[y];
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
	if (ray->column <= MINIMAP_SIZE && y <= MINIMAP_SIZE)
		y = MINIMAP_SIZE;
	while (++y < ray->draw_end)
	{
		d = y * 256 - HEIGHTX128 + ray->line_height * 128;
		ray->tex_y = (d * text->height) / (ray->line_height * 256);
		if (ray->tex_y < 0)
			ray->tex_y = 0;
		color = get_pixel_value(text, ray->tex_x, ray->tex_y);
		*(int *)(vars->display->data + y * PXL_LINE + ray->column * 4) \
			= d_c(color, ray->distance * 10);
	}
	draw_floor_and_ceiling(vars, ray, ray->draw_start, ray->draw_end);
}
