/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:17:55 by hamzaelouar       #+#    #+#             */
/*   Updated: 2023/09/10 13:57:29 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_alloc_floor_ceiling(t_infos *vars)
{
	vars->map->floor = garb_col_mlx(vars, ALLOC, sizeof(t_color), NULL);
	if (!vars->map->floor)
		return (0);
	vars->map->floor->color_nb = 8421504;
	vars->map->ceil = garb_col_mlx(vars, ALLOC, sizeof(t_color), NULL);
	if (!vars->map->ceil)
		return (0);
	vars->map->ceil->color_nb = 88900331;
	vars->map->b_g = garb_col_mlx(vars, ALLOC, RES_H * sizeof(int), NULL);
	if (!vars->map->b_g)
		return (0);
	return (1);
}

int	alloc_floor_ceiling(t_infos *vars)
{
	int		y;
	double	t;

	y = 0;
	if (!init_alloc_floor_ceiling(vars))
		return (0);
	while (y < RES_H)
	{
		if (y < RES_HALF_HEIGHT * 0.5)
			vars->map->b_g[y] = vars->map->ceil->color_nb;
		else if (y < RES_HALF_HEIGHT)
		{
			t = (double)(y - RES_HALF_HEIGHT * 0.5) / (RES_HALF_HEIGHT * 0.5);
			t = pow(t, 2);
			vars->map->b_g[y] = d_c(vars->map->ceil->color_nb, (int)(150 * t));
		}
		else if (y > RES_H - RES_HALF_HEIGHT)
		{
			t = (double)(y - RES_H) / RES_HALF_HEIGHT;
			t = pow(t, 2);
			vars->map->b_g[y] = d_c(vars->map->floor->color_nb, (int)(150 * t));
		}
		y++;
	}
	return (1);
}

static int	color_to_int(t_color *col_infos, char **color)
{
	int	rgb[3];
	int	curr_col;
	int	*nb;

	curr_col = 0;
	nb = &col_infos->color_nb;
	while (color[curr_col + 1])
	{
		rgb[curr_col] = ft_atoi(color[curr_col + 1]);
		if (rgb[curr_col] < 0 || rgb[curr_col] > 255)
			return (-1);
		curr_col++;
		if (curr_col == 3 && color[curr_col + 1] != NULL)
			return (-1);
	}
	*nb = ((rgb[0] & 0xFF) << 16 | (rgb[1] & 0xFF) << 8 | (rgb[2] & 0xFF));
	return (1);
}

int	map_infos(t_infos *vars, t_map *map)
{
	char	**splited;
	int		is_infos;

	if (!ft_strncmp(map->line, "", 1) || !ft_strncmp(map->line, "\n", 2))
		return (1);
	splited = ft_specific_split(map->line, " ,\n", vars);
	if (!splited)
		return (0);
	is_infos = 1;
	if (splited && !ft_strncmp(splited[0], "NO", 2))
		map->no = garb_col_mlx(vars, TEXTURE, 0, splited[1]);
	else if (splited && !ft_strncmp(splited[0], "SO", 2))
		map->so = garb_col_mlx(vars, TEXTURE, 0, splited[1]);
	else if (splited && !ft_strncmp(splited[0], "EA", 2))
		map->ea = garb_col_mlx(vars, TEXTURE, 0, splited[1]);
	else if (splited && !ft_strncmp(splited[0], "WE", 2))
		map->we = garb_col_mlx(vars, TEXTURE, 0, splited[1]);
	else if (splited && !ft_strncmp(splited[0], "F", 2))
		return (color_to_int(map->floor, splited));
	else if (splited && !ft_strncmp(splited[0], "C", 2))
		return (color_to_int(map->ceil, splited));
	else
		is_infos = 0;
	return (is_infos);
}

void	place_player(t_infos *vars, t_map *map, int i, int j)
{
	if (map->grid[i][j] == 'N')
	{
		vars->player->dir_y = -1.0;
		vars->player->plan_x = -0.66;
	}
	else if (map->grid[i][j] == 'S')
	{
		vars->player->dir_y = 1.0;
		vars->player->plan_x = 0.66;
	}
	else if (map->grid[i][j] == 'E')
	{
		vars->player->dir_x = 1.0;
		vars->player->plan_y = -0.66;
	}
	else if (map->grid[i][j] == 'W')
	{
		vars->player->dir_x = -1.0;
		vars->player->plan_y = 0.66;
	}
	map->grid[i][j] = '0';
	vars->player->y = i + 0.5;
	vars->player->x = j + 0.5;
}
