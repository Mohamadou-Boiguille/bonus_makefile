/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:03:05 by hamzaelouar       #+#    #+#             */
/*   Updated: 2023/09/10 19:03:08 by hamzaelouar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	exit_cross(t_infos *vars)
{
	exit_game(vars, "Au revoir !", 0);
	return (0);
}

int	check_filename(char *filename)
{
	if (ft_strncmp(filename + ft_strlen(filename) - 4, ".cub", 5))
		return (-1);
	return (open(filename, O_RDONLY));
}

int	ft_strichr(char *str, int c)
{
	size_t	index;

	index = 0;
	while (str[index])
		if (str[index++] == c)
			return (index - 1);
	return (-1);
}

int	render(t_infos *vars)
{
	static int	not_first_time;
	int			img_displayed;

	img_displayed = 0;
	if (all_keys_released(vars) && not_first_time)
		return (0);
	not_first_time = 1;
	move_player(vars);
	cast_all_rays(vars);
	img_displayed = mlx_put_image_to_window(vars->mlx, vars->win, vars->display,
			0, 0);
	if (img_displayed == -1)
		printf("display error\n");
	if (!vars->display)
		exit_game(vars, "render(): failed to put image to window", 78);
	return (0);
}

int	main(int argc, char **argv)
{
	t_infos	*vars;
	int		exit_code;
	int		fd;

	exit_code = 0;
	if (argc != 2)
		return (printf("Error\nNeed one map file\n"));
	fd = check_filename(argv[1]);
	if (fd < 0)
		return (printf("Error\nfile opening error\n"));
	vars = init_vars(fd);
	if (!vars)
		return (printf("init vars failed\n"), 1);
	mlx_hook(vars->win, DestroyNotify, 1L << 17, &exit_cross, vars);
	mlx_hook(vars->win, KeyPress, KeyPressMask, key_press, vars);
	mlx_hook(vars->win, KeyRelease, KeyReleaseMask, key_release, vars);
	mlx_loop_hook(vars->mlx, &render, vars);
	mlx_loop(vars->mlx);
	return (exit_code);
}
