/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:58:22 by moboigui          #+#    #+#             */
/*   Updated: 2023/09/10 19:02:42 by hamzaelouar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

int	key_press(int key, t_infos *vars)
{
	if (key == 65307 || key == 53)
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
