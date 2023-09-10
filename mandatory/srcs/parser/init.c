/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:03:45 by hamzaelouar       #+#    #+#             */
/*   Updated: 2023/09/10 19:03:48 by hamzaelouar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static t_player	*init_player(t_infos *vars)
{
	t_player	*player;

	player = garb_col_mlx(vars, ALLOC, sizeof(t_player), NULL);
	if (!player)
		exit_game(vars, "failed init player", 1);
	player->x = -1;
	player->y = -1;
	return (player);
}

static void	init_screen(t_infos *vars)
{
	vars->mlx = garb_col_mlx(vars, MLX, 0, NULL);
	if (!vars->mlx)
		exit_game(vars, "failed to create mlx (init_screen)", 1);
	vars->win = garb_col_mlx(vars, WIN, 0, NULL);
	if (!vars->win)
		exit_game(vars, "failed to create window (init_screen)", 1);
}

static t_img	*init_image(t_infos *vars)
{
	t_img	*display;

	display = garb_col_mlx(vars, IMG, 0, NULL);
	if (!display)
		exit_game(vars, "failed to create display (init_image)", 1);
	return (display);
}

t_infos	*init_vars(int fd)
{
	t_infos	*vars;

	vars = ft_calloc(1, sizeof(t_infos));
	if (!vars)
		return (NULL);
	vars->width = RES_W;
	vars->height = RES_H;
	vars->fd = fd;
	vars->player = init_player(vars);
	init_screen(vars);
	vars->display = init_image(vars);
	vars->fback = garb_col_mlx(vars, ALLOC, sizeof(t_fback), NULL);
	vars->fback->pattern_size = 8;
	vars->map = load_map(vars);
	if (!vars->map)
		exit_game(vars, "map loading error", 5);
	vars->move_speed = 0.05;
	vars->rot_speed = 0.03;
	return (vars);
}

void	init_floor_and_ceiling(t_infos *vars, int *vert_line)
{
	int			i;
	static int	is_initialized;

	if (is_initialized)
		return ;
	i = 0;
	while (i < RES_H)
	{
		if (i < RES_HALF_HEIGHT)
			vert_line[i] = vars->map->ceiling->color_nb;
		else
			vert_line[i] = vars->map->floor->color_nb;
		i++;
	}
	is_initialized = 1;
}
