/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:58:37 by moboigui          #+#    #+#             */
/*   Updated: 2023/09/10 19:04:02 by hamzaelouar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_collision(t_map *map, double x, double y)
{
	if (has_wall_at(map, x, y))
		return (1);
	if (has_wall_at(map, x + 0.2, y))
		return (1);
	if (has_wall_at(map, x - 0.2, y))
		return (1);
	if (has_wall_at(map, x, y + 0.2))
		return (1);
	if (has_wall_at(map, x, y - 0.2))
		return (1);
	if (has_wall_at(map, x + 0.2, y + 0.2))
		return (1);
	if (has_wall_at(map, x - 0.2, y - 0.2))
		return (1);
	return (0);
}

static void	up_down(double *new_x, double *new_y, t_infos *vars)
{
	t_player	*pl;

	pl = vars->player;
	if (pl->up && !pl->down)
	{
		*new_x = pl->x + pl->dir_x * vars->move_speed;
		*new_y = pl->y + pl->dir_y * vars->move_speed;
	}
	else if (pl->down && !pl->up)
	{
		*new_x = pl->x - pl->dir_x * vars->move_speed;
		*new_y = pl->y - pl->dir_y * vars->move_speed;
	}
}

static void	left_right(t_infos *vars, int coeff)
{
	double		rot;
	t_player	*pl;
	double		temp_dir_x;
	double		temp_plan_x;

	pl = vars->player;
	rot = vars->rot_speed * coeff;
	temp_dir_x = pl->dir_x;
	pl->dir_x = pl->dir_x * cos(rot) - pl->dir_y * sin(rot);
	pl->dir_y = temp_dir_x * sin(rot) + pl->dir_y * cos(rot);
	temp_plan_x = pl->plan_x;
	pl->plan_x = pl->plan_x * cos(rot) - pl->plan_y * sin(rot);
	pl->plan_y = temp_plan_x * sin(rot) + pl->plan_y * cos(rot);
}

void	move_player(t_infos *vars)
{
	double		new_x;
	double		new_y;
	t_player	*pl;

	pl = vars->player;
	new_x = pl->x;
	new_y = pl->y;
	up_down(&new_x, &new_y, vars);
	if (pl->right && !pl->left)
		left_right(vars, 1);
	if (pl->left && !pl->right)
		left_right(vars, -1);
	if (!check_collision(vars->map, new_x, new_y))
	{
		pl->x = new_x;
		pl->y = new_y;
	}
	else if (!check_collision(vars->map, new_x, pl->y))
		pl->x = new_x;
	else if (!check_collision(vars->map, pl->x, new_y))
		pl->y = new_y;
}
