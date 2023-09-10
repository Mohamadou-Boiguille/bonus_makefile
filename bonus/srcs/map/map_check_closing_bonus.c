/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_closing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:17:45 by hamzaelouar       #+#    #+#             */
/*   Updated: 2023/09/10 12:39:39 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_closed(t_map *map, int visited[128][128], int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
	{
		write(1, "aie", 3);
		return (0);
	}
	if (visited[y][x])
		return (1);
	else
		visited[y][x] = 1;
	if (map->grid[y][x] == '1')
		return (1);
	if (is_closed(map, visited, x - 1, y) && is_closed(map, visited, x + 1, y)
		&& is_closed(map, visited, x, y - 1) 
		&& is_closed(map, visited, x, y + 1))
		return (1);
	return (0);
}

int	is_surrounded_by_walls(t_map *map, int x, int y)
{
	int	i;
	int	j;
	int	visited[128][128];

	i = 0;
	while (i < 128)
	{
		j = 0;
		while (j < 128)
			visited[i][j++] = 0;
		i++;
	}
	if (is_closed(map, visited, x, y))
		return (1);
	return (0);
}

void	*create_wall_texture(t_infos *vars, int color1, int color2)
{
	int		x;
	int		y;
	t_fback	*fb;
	int		*wall_data;
	int		wall_texture[FB_SIZE * FB_SIZE];

	fb = vars->fback;
	y = -1;
	while (++y < FB_SIZE)
	{
		x = -1;
		while (++x < FB_SIZE)
		{
			if ((x % fb->pattern_size == 0) || (y % fb->pattern_size == 0))
				wall_texture[y * FB_SIZE + x] = color1;
			else
				wall_texture[y * FB_SIZE + x] = color2;
		}
	}
	fb->ptr = garb_col_mlx(vars, FB_TEXTURE, 0, NULL);
	wall_data = (int *)mlx_get_data_addr(fb->ptr, &fb->bpp, \
		&fb->size_l, &fb->endian);
	ft_memcpy(wall_data, wall_texture, FB_SIZE * FB_SIZE * sizeof(int));
	return (fb->ptr);
}

void	create_fallback_textures(t_infos *vars)
{
	if (vars->map->no == NULL)
		vars->map->no = create_wall_texture(vars, N_COLOR1, N_COLOR2);
	if (vars->map->so == NULL)
		vars->map->so = create_wall_texture(vars, S_COLOR1, N_COLOR2);
	if (vars->map->ea == NULL)
		vars->map->ea = create_wall_texture(vars, E_COLOR1, N_COLOR2);
	if (vars->map->we == NULL)
		vars->map->we = create_wall_texture(vars, W_COLOR1, N_COLOR2);
}
