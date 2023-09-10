/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzaelouardi <hamzaelouardi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:16:06 by moboigui          #+#    #+#             */
/*   Updated: 2023/09/10 19:00:40 by hamzaelouar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define PXL_LINE 5120 //RES_W * 4
# define HEIGHTX128 102400 //RES_H * 128
# define RES_W 1280
# define RES_HALF_WIDTH 640
# define RES_H 800
# define RES_HALF_HEIGHT 400
# define RATIO 1.77777777778
# define ESCAPE 999
# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100
# define ARROW_R 65363
# define ARROW_L 65361
# define SHADOW_FACTOR 15
# define FB_SIZE 64
# define ALLOC 0
# define MLX 1
# define WIN 2
# define IMG 3
# define TEXTURE 4
# define FB_TEXTURE 5
# define N_COLOR1 0xBBBBBB
# define N_COLOR2 0x999999
# define S_COLOR1 0x87CEEB
# define S_COLOR2 0xFFFFFF
# define E_COLOR1 0xFFE066
# define E_COLOR2 0x8B4513
# define W_COLOR1 0xFF5733
# define W_COLOR2 0x2C3E50

# include "../libft/src/libft.h"
# include "get_next_line.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"
# include <X11/X.h>
# include <ctype.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_fback
{
	void				*ptr;
	int					size_l;
	int					bpp;
	int					endian;
	int					width;
	int					height;
	int					pattern_size;
}						t_fback;

typedef struct s_color
{
	char				*path;
	void				*ptr;
	char				**color;
	void				*addr;
	int					color_nb;
}						t_color;

typedef struct s_step
{
	double				map_x;
	double				map_y;
	double				step_x;
	double				step_y;
}						t_step;

typedef struct s_minimap
{
	int					x_offset;
	int					y_offset;
	int					x;
	int					y;
	int					position;
}						t_minimap;

typedef struct s_player
{
	double				x;
	double				y;
	double				delta_x;
	double				delta_y;
	double				plan_x;
	double				plan_y;
	double				dir_x;
	double				dir_y;
	int					up;
	int					down;
	int					left;
	int					right;
	int					arrow_l;
	int					arrow_r;
}						t_player;

typedef struct s_map
{
	int					width;
	int					height;
	char				**grid;
	void				*no;
	void				*so;
	void				*ea;
	void				*we;
	char				*line;
	t_color				*floor;
	t_color				*ceiling;
}						t_map;

typedef struct s_garbage
{
	void				*ptr;
	int					type;
	struct s_garbage	*next;
}						t_garbage;

typedef struct s_infos
{
	t_player			*player;
	void				*mlx;
	void				*win;
	t_map				*map;
	double				move_speed;
	double				rot_speed;
	t_img				*display;
	int					fd;
	t_garbage			*garbage;
	t_fback				*fback;
	int					height;
	int					width;
}						t_infos;

typedef struct s_ray
{
	double				distance;
	int					wall_side;
	int					wall_color;
	int					hit;
	double				dir_x;
	double				dir_y;
	double				hit_x;
	double				hit_y;
	int					column;
	int					line_height;
	int					draw_start;
	int					draw_end;
	double				wall_x;
	t_img				*tex;
	int					tex_x;
	int					tex_y;
	int					tex_num;
	t_infos				*vars;
}						t_ray;

void					mlx_draw_line(t_infos *vars, int x2, int y2, int color);
// init.c
t_infos					*init_vars(int fd);
void					init_floor_and_ceiling(t_infos *vars, int *vert_line);
// map.c
t_map					*load_map(t_infos *vars);
// map_data.c
int						map_infos(t_infos *vars, t_map *map);
int						alloc_floor_ceiling(t_infos *vars);
void					place_player(t_infos *vars, t_map *map, int i, int j);
// display.c
void					draw_minimap(t_infos *vars);
void					draw_vertical_line(t_infos *vars, t_ray *ray);
// movements.c
int						all_keys_released(t_infos *vars);
int						key_press(int key, t_infos *vars);
int						key_release(int key, t_infos *vars);
void					move_player(t_infos *vars);
// raycasting.c
void					cast_all_rays(t_infos *vars);
// raycasting_helpers.c
int						wall_orientation(double dir_x, double dir_y,
							t_ray *ray);
void					set_wall_distance(t_ray *ray, t_player *pl);
void					init_side_distances(t_ray *ray, t_player *pl,
							t_step *steps);
void					get_drawing_sizes(t_ray *ray);
t_img					*find_texture(t_infos *vars, t_ray *ray);
// minilibft.c
int						ft_strichr(char *str, int c);
void					free_split(char **array);
char					**ft_specific_split(char *str, char *delims, \
						t_infos *vars);
// helpers.c
int						has_wall_at(t_map *map, double x, double y);
void					exit_game(t_infos *vars, char *msg, int code);
int						get_pixel_value(t_img *img, int x, int y);
// map_check_closing.c
int						is_surrounded_by_walls(t_map *map, int x, int y);
void					create_fallback_textures(t_infos *vars);
// garbage_collector.c
void					*garb_col_mlx(t_infos *vars, int type, size_t size,
							char *filename);
void					free_garb_col_mlx(t_infos *vars);

#endif
