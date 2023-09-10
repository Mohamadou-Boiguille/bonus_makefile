/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:18:18 by hamzaelouar       #+#    #+#             */
/*   Updated: 2023/09/10 13:55:29 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	free(map->no);
	free(map->so);
	free(map->ea);
	free(map->we);
	free(map->floor);
	free(map->ceil);
	while (map->grid && i < map->height)
		free(map->grid[i++]);
	free(map->grid);
}

void	exit_game(t_infos *vars, char *msg, int code)
{
	if (code)
		printf("Error\n");
	printf("%s\n", msg);
	free_garb_col_mlx(vars);
	exit(code);
}

int	has_wall_at(t_map *map, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = floor(x);
	map_y = floor(y);
	if (map_x < 0 || map_x >= map->width || map_y < 0 || map_y >= map->height)
		return (-1);
	if (map->grid[map_y][map_x] == 'D')
		return (2);
	if (map->grid[map_y][map_x] != '0')
		return (1);
	return (0);
}

int	d_c(int color, int amount)
{
	int	red;
	int	green;
	int	blue;

	if (amount < 0 || amount > 255)
		return (0);
	red = (color >> 16) & 0xFF;
	green = (color >> 8) & 0xFF;
	blue = color & 0xFF;
	red -= amount;
	green -= amount;
	blue -= amount;
	if (red < 0)
		red = 0;
	if (green < 0)
		green = 0;
	if (blue < 0)
		blue = 0;
	return ((red << 16) | (green << 8) | blue);
}

int	get_pixel_value(t_img *img, int x, int y)
{
	char	*ptr;
	int		value;

	ptr = img->data + (y * img->size_line) + (x << 2);
	value = *((int *)ptr);
	return (value);
}
