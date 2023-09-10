/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ouar <hel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:18:03 by hamzaelouar       #+#    #+#             */
/*   Updated: 2023/09/10 12:45:25 by hel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_map(t_infos *vars, t_map *map)
{
	char	*is_player;
	int		player_found;
	int		i;
	int		j;

	i = -1;
	player_found = 0;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			is_player = ft_strchr("NSEW", map->grid[i][j]);
			if (is_player && player_found)
				exit_game(vars, "more than one player", 42);
			if (is_player)
			{
				place_player(vars, map, i, j);
				player_found = 1;
			}
			else if (!ft_strchr(" 01D\n", map->grid[i][j]))
				exit_game(vars, "invalid character in map", 25);
		}
	}
	return (1);
}

static int	copy_map(t_infos *vars, char *temp[128], char *line)
{
	int	i;
	int	max_width;
	int	temp_width;

	i = 0;
	max_width = 0;
	temp_width = 0;
	while (line)
	{
		temp[i++] = line;
		temp_width = ft_strlen(line);
		if (temp_width > max_width)
			max_width = temp_width;
		if (temp_width > 128 || i >= 128)
			return (0);
		line = get_next_line(vars->fd);
	}
	vars->map->width = max_width;
	vars->map->height = i;
	vars->map->grid = garb_col_mlx(vars, ALLOC, i * sizeof(char *), NULL);
	if (!vars->map->grid)
		return (0);
	return (1);
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

static int	parse_map(t_infos *vars, char **line)
{
	int		i;
	int		temp_width;
	char	*temp[128];

	if (!copy_map(vars, temp, *line))
		exit_game(vars, "parse_map: error", 198);
	i = 0;
	while (i < vars->map->height)
	{
		vars->map->grid[i] = garb_col_mlx(vars, ALLOC, \
			(vars->map->width + 1) * sizeof(char), NULL);
		temp_width = ft_strlen(temp[i]);
		ft_strncpy(vars->map->grid[i], temp[i], --temp_width);
		free(temp[i]);
		vars->map->grid[i][vars->map->width] = '\0';
		while (temp_width < vars->map->width)
			vars->map->grid[i][temp_width++] = ' ';
		i++;
	}
	check_map(vars, vars->map);
	if (vars->player->x == -1 || vars->player->y == -1)
		exit_game(vars, "no player ", 22);
	return (1);
}

t_map	*load_map(t_infos *vars)
{
	int	map_data;

	vars->map = garb_col_mlx(vars, ALLOC, sizeof(t_map), NULL);
	if (!vars->map || !alloc_floor_ceiling(vars))
		exit_game(vars, "alloc map failed", 48);
	vars->map->height = 0;
	vars->map->line = get_next_line(vars->fd);
	while (vars->map->line)
	{
		map_data = map_infos(vars, vars->map);
		if (!map_data)
			break ;
		if (map_data < 0)
			exit_game(vars, "error in map infos", 48);
		free(vars->map->line);
		vars->map->line = get_next_line(vars->fd);
	}
	if (!parse_map(vars, &vars->map->line))
		exit_game(vars, "map error (load map)\n", 206);
	if (!is_surrounded_by_walls(vars->map, vars->player->x, vars->player->y))
		exit_game(vars, "map not surrounded by walls (load map)\n", 206);
	create_fallback_textures(vars);
	close(vars->fd);
	return (vars->map);
}
