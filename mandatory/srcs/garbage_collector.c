/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 04:26:35 by moboigui          #+#    #+#             */
/*   Updated: 2023/09/10 19:02:32 by hamzaelouar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	garb_mlx(t_infos *vars, t_garbage *garbage)
{
	if (garbage->type == MLX)
		garbage->ptr = mlx_init();
	else if (garbage->type == WIN)
		garbage->ptr = mlx_new_window(vars->mlx, vars->width, vars->height,
				"Cub3d");
	if (!garbage->ptr)
		exit_game(vars, "failed to init windows", 2);
}

void	garb_img(t_infos *vars, t_garbage *garbage, char *filename)
{
	int	width;
	int	height;

	if (garbage->type == IMG)
		garbage->ptr = mlx_new_image(vars->mlx, vars->width, vars->height);
	else if (garbage->type == FB_TEXTURE)
		garbage->ptr = mlx_new_image(vars->mlx, FB_SIZE, FB_SIZE);
	else if (garbage->type == TEXTURE)
	{
		garbage->ptr = mlx_xpm_file_to_image(vars->mlx, filename, &width, \
		&height);
	}
	if (!garbage->ptr)
	{
		free(vars->map->line);
		exit_game(vars, "loading texture failed", 1);
	}
}

void	*garb_col_mlx(t_infos *vars, int type, size_t size, char *filename)
{
	t_garbage	*new_garbage;

	new_garbage = malloc(sizeof(t_garbage));
	if (new_garbage == NULL)
		exit_game(vars, "failed to allocate memory (garb_col_mlx)", 1);
	new_garbage->type = type;
	new_garbage->next = vars->garbage;
	vars->garbage = new_garbage;
	if (type == ALLOC)
	{
		new_garbage->ptr = ft_calloc(1, size);
		if (!new_garbage->ptr)
			exit_game(vars, "failed to allocate memory (garb_col_mlx)", 1);
	}
	else if (type == MLX || type == WIN)
		garb_mlx(vars, new_garbage);
	else if (type == IMG || type == TEXTURE || type == FB_TEXTURE)
		garb_img(vars, new_garbage, filename);
	return (new_garbage->ptr);
}

void	free_garb_col_mlx(t_infos *vars)
{
	t_garbage	*next_garbage;

	while (vars->garbage != NULL)
	{
		next_garbage = vars->garbage->next;
		if (vars->garbage->type == ALLOC && vars->garbage->ptr)
			free(vars->garbage->ptr);
		else if (vars->garbage->type == MLX && vars->garbage->ptr)
			mlx_destroy_display((t_xvar *)vars->mlx);
		else if (vars->garbage->type == WIN && vars->garbage->ptr)
			mlx_destroy_window(vars->mlx, vars->garbage->ptr);
		else if (vars->garbage->type == IMG && vars->garbage->ptr)
			mlx_destroy_image(vars->mlx, vars->garbage->ptr);
		else if (vars->garbage->type == TEXTURE && vars->garbage->ptr)
			mlx_destroy_image(vars->mlx, vars->garbage->ptr);
		else if (vars->garbage->type == FB_TEXTURE && vars->garbage->ptr)
			mlx_destroy_image(vars->mlx, vars->garbage->ptr);
		free(vars->garbage);
		vars->garbage = next_garbage;
	}
	free((t_xvar *)vars->mlx);
	free(vars);
	vars = NULL;
}
