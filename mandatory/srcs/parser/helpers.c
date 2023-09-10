/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:58:09 by moboigui          #+#    #+#             */
/*   Updated: 2023/09/10 19:03:32 by hamzaelouar      ###   ########.fr       */
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
	free(map->ceiling);
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
	if (map->grid[map_y][map_x] != '0')
		return (1);
	return (0);
}

int	get_pixel_value(t_img *img, int x, int y)
{
	char	*ptr;
	int		value;

	ptr = img->data + (y * img->size_line) + (x << 2);
	value = *((int *)ptr);
	return (value);
}
