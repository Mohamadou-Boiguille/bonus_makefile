/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:18:59 by hamzaelouar       #+#    #+#             */
/*   Updated: 2023/09/10 13:17:57 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

int	all_keys_released(t_infos *vars)
{
	if (vars->player->up == 1)
		return (0);
	if (vars->player->down == 1)
		return (0);
	if (vars->player->left == 1)
		return (0);
	if (vars->player->right == 1)
		return (0);
	if (vars->player->arrow_l == 1)
		return (0);
	if (vars->player->arrow_r == 1)
		return (0);
	return (1);
}

void	manage_mouse(t_infos *vars)
{
	static int	old_x;
	static int	x;
	static int	y;

	(void)y;
	vars->player->arrow_l = 0;
	vars->player->arrow_r = 0;
	if (x == 0)
	{
		mlx_mouse_get_pos(vars->mlx, vars->win, &x, &y);
		old_x = x;
	}
	mlx_mouse_get_pos(vars->mlx, vars->win, &x, &y);
	if (x > old_x)
		vars->player->arrow_r = 1;
	else if (x < old_x)
		vars->player->arrow_l = 1;
	old_x = x;
	fflush(stdout);
}

int	key_press(int key, t_infos *vars)
{
	if (key == ESCAPE)
		exit_game(vars, "Au revoir", 0);
	else if (key == UP)
		vars->player->up = 1;
	else if (key == DOWN)
		vars->player->down = 1;
	else if (key == LEFT)
		vars->player->left = 1;
	else if (key == RIGHT)
		vars->player->right = 1;
	else if (key == ARROW_L)
		vars->player->arrow_l = 1;
	else if (key == ARROW_R)
		vars->player->arrow_r = 1;
	return (0);
}

int	key_release(int key, t_infos *vars)
{
	if (key == UP)
		vars->player->up = 0;
	else if (key == DOWN)
		vars->player->down = 0;
	else if (key == LEFT)
		vars->player->left = 0;
	else if (key == RIGHT)
		vars->player->right = 0;
	else if (key == ARROW_L)
		vars->player->arrow_l = 0;
	else if (key == ARROW_R)
		vars->player->arrow_r = 0;
	return (0);
}
