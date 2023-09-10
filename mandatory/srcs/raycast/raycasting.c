/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:58:51 by moboigui          #+#    #+#             */
/*   Updated: 2023/09/10 19:04:14 by hamzaelouar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_ray(t_infos *vars, int column, t_ray *ray)
{
	t_player		*pl;
	double			camera;
	static double	inverse_width;

	if (!inverse_width)
		inverse_width = 1.0 / (double)vars->width;
	pl = vars->player;
	camera = 1 - 2.0 * ray->column * inverse_width;
	ray->dir_x = pl->dir_x + pl->plan_x * camera;
	ray->dir_y = pl->dir_y + pl->plan_y * camera;
	if (ray->dir_x == 0)
		pl->delta_x = 1e30;
	else
		pl->delta_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0)
		pl->delta_y = 1e30;
	else
		pl->delta_y = fabs(1.0 / ray->dir_y);
	ray->hit = 0;
	ray->hit_x = 0;
	ray->hit_y = 0;
	ray->column = column;
	ray->wall_side = 0;
	ray->distance = 0;
	ray->vars = vars;
}

static void	perform_dda(t_infos *vars, t_ray *ray, t_step *steps)
{
	t_player	*pl;

	pl = vars->player;
	while (!ray->hit)
	{
		if (ray->hit_x < ray->hit_y)
		{
			ray->hit_x += pl->delta_x;
			steps->map_x += steps->step_x;
			ray->wall_side = 0;
		}
		else
		{
			ray->hit_y += pl->delta_y;
			steps->map_y += steps->step_y;
			ray->wall_side = 1;
		}
		if (has_wall_at(vars->map, steps->map_x, steps->map_y))
			ray->hit = 1;
	}
}

static void	raycast(t_infos *vars, t_ray *ray)
{
	t_player	*pl;
	t_step		steps;

	pl = vars->player;
	init_side_distances(ray, pl, &steps);
	perform_dda(vars, ray, &steps);
	set_wall_distance(ray, pl);
	get_drawing_sizes(ray);
	ray->tex = find_texture(vars, ray);
	if (ray->wall_side)
		ray->wall_x = pl->x + ray->distance * ray->dir_x;
	else
		ray->wall_x = pl->y + ray->distance * ray->dir_y;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)ray->tex->width);
	if (!ray->wall_side && ray->dir_x > 0)
		ray->tex_x = ray->tex->width - ray->tex_x - 1;
	if (ray->wall_side && ray->dir_y < 0)
		ray->tex_x = ray->tex->width - ray->tex_x - 1;
}

void	cast_all_rays(t_infos *vars)
{
	int		x;
	t_ray	*ray;

	x = 0;
	ray = garb_col_mlx(vars, ALLOC, sizeof(t_ray), NULL);
	while (x < vars->width)
	{
		init_ray(vars, x, ray);
		raycast(vars, ray);
		draw_vertical_line(vars, ray);
		x++;
	}
}
