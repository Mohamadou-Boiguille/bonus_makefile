/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:04:06 by hamzaelouar       #+#    #+#             */
/*   Updated: 2023/09/10 19:04:09 by hamzaelouar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_wall_distance(t_ray *ray, t_player *pl)
{
	if (!ray->wall_side)
		ray->distance = ray->hit_x - pl->delta_x;
	else
		ray->distance = ray->hit_y - pl->delta_y;
}

void	init_side_distances(t_ray *ray, t_player *pl, t_step *steps)
{
	steps->map_x = (int)pl->x;
	steps->map_y = (int)pl->y;
	if (ray->dir_x < 0)
	{
		steps->step_x = -1;
		ray->hit_x = (pl->x - steps->map_x) * pl->delta_x;
	}
	else
	{
		steps->step_x = 1;
		ray->hit_x = (steps->map_x + 1.0 - pl->x) * pl->delta_x;
	}
	if (ray->dir_y < 0)
	{
		steps->step_y = -1;
		ray->hit_y = (pl->y - steps->map_y) * pl->delta_y;
	}
	else
	{
		steps->step_y = 1;
		ray->hit_y = (steps->map_y + 1.0 - pl->y) * pl->delta_y;
	}
}

void	get_drawing_sizes(t_ray *ray)
{
	ray->line_height = (int)(ray->vars->height / ray->distance);
	ray->draw_start = (-ray->line_height >> 1) + RES_HALF_HEIGHT;
	ray->draw_end = (ray->line_height >> 1) + RES_HALF_HEIGHT;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= ray->vars->height)
		ray->draw_end = ray->vars->height - 1;
}

t_img	*find_texture(t_infos *vars, t_ray *ray)
{
	if (ray->wall_side == 0 && ray->dir_x < 0)
		return ((t_img *)vars->map->ea);
	if (ray->wall_side == 0 && ray->dir_x >= 0)
		return ((t_img *)vars->map->we);
	if (ray->wall_side == 1 && ray->dir_y < 0)
		return ((t_img *)vars->map->no);
	else
		return ((t_img *)vars->map->so);
}
