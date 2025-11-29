/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:58:59 by liliu             #+#    #+#             */
/*   Updated: 2025/11/29 20:52:22 by liliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 768

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define CLOSE_WINDOW 17

# define WALL_NORTH 0
# define WALL_SOUTH 1
# define WALL_EAST 2
# define WALL_WEST 3

# define TEX_NO 0
# define TEX_SO 1
# define TEX_EA 2
# define TEX_WE 3

# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

/* Image */
typedef struct s_img
{
	void    *img;
	char    *addr;
	int     width;
	int     height;
	int     bpp;
	int     line_len;
	int     endian;
}   t_img;

/* Texture */
typedef struct s_texture
{
	void    *img;
	char    *addr;
	int     width;
	int     height;
	int     bpp;
	int     line_len;
	int     endian;
}   t_texture;

/* Player */
typedef struct s_player
{
	double  x;
	double  y;
	double  dir_x;
	double  dir_y;
	double  plane_x;
	double  plane_y;
}   t_player;

/* Keys */
typedef struct s_keys
{
	int     w;
	int     a;
	int     s;
	int     d;
	int     left;
	int     right;
}   t_keys;

/* Ray */
typedef struct s_ray
{
    double      camera_x;
    double      dir_x;
    double      dir_y;
    int         map_x;
    int         map_y;
    double      side_dist_x;
    double      side_dist_y;
    double      delta_dist_x;
    double      delta_dist_y;
    double      perp_wall_dist;
    double      distance;
    int         step_x;
    int         step_y;
    int         hit;
    int         side;
    int         line_height;
    int         draw_start;
    int         draw_end;
    double      wall_x;
    int         tex_x;
    int         wall_type;
}   t_ray;

/* Map */
typedef struct s_map
{
	char    **grid;
	int     width;
	int     height;
	char    *n_texture;
	char    *s_texture;
	char    *e_texture;
	char    *w_texture;
	int     floor_color;
	int     ceiling_color;
}   t_map;

/* Game */
typedef struct s_game
{
	void        *mlx;
	void        *win;
	t_img       *img;
	t_map       *map;
	t_player    *player;
	t_texture   textures[4];
	t_keys      keys;// 添加键盘状态
}   t_game;

/* ------------------ DRAWING FUNCTIONS ------------------ */
void    draw_ceiling_floor(t_game *game, int x, int draw_start, int draw_end);
void    draw_wall_strip(t_game *game, t_ray *ray, int x);
void    draw_wall_pixels(t_game *game, t_ray *ray, int x, t_texture *texture);
void    draw_wall_loop(t_game *game, t_ray *ray, int x,
				t_texture *texture, int draw_start, int draw_end, int line_height);

/* parameters for rendering a single wall column (kept for clarity) */
typedef struct s_wall_render_params
{
	t_game      *game;
	t_texture   *texture;
	t_ray       *ray;
	int         tex_x;
	int         draw_start;
	int         draw_end;
	int         line_height;
	int         x;
}   t_wall_render_params;

/* draw helper prototypes */
void    calc_draw_range(t_ray *ray, int *line_height,
				int *draw_start, int *draw_end);

/* Helpers */
t_texture   *select_texture(t_game *game, t_ray *ray);
int         calc_tex_x(t_ray *ray, t_texture *texture, t_player *player);
int         calc_tex_y(double *tex_pos, t_texture *texture, double step);
int         get_shaded_color(t_ray *ray, int color);

/* ------------------ PIXEL / IMAGE FUNCTIONS ------------------ */
void    put_pixel(t_img *img, int x, int y, int color);
int     get_texture_color(t_texture *texture, int tx, int ty);
void    clear_image(t_img *img);

/* ------------------ RAYCASTING FUNCTIONS ------------------ */
void    init_dda(t_game *game, t_ray *ray);
void    perform_dda(t_game *game, t_ray *ray);
void    calculate_wall_distance(t_game *game, t_ray *ray);
void    calculate_ray_direction(t_game *game, t_ray *ray, int x);
void    cast_ray(t_game *game, t_ray *ray);
/* DDA: public API */
void    perform_dda(t_game *game, t_ray *ray);

/* ------------------ CLEANUP / FREE FUNCTIONS ------------------ */
void    free_map(t_map *map);
void    free_textures(t_game *game);
void    cleanup_game(t_game *game);

/*---------------------------------------------------------*/
/* Input / Movement / Rotation Prototypes */
int     handle_keypress(int keycode, t_game *game);
int     handle_keyrelease(int keycode, t_game *game);
int     close_game(t_game *game);
void    move_forward(t_game *game);
void    move_backward(t_game *game);
void    move_left(t_game *game);
void    move_right(t_game *game);
void    rotate_left(t_game *game);
void    rotate_right(t_game *game);
void    update_player(t_game *game);

/*---------------------------------------------------------*/
void    error_exit(char *msg);


/*---------------------------------------------------------*/
/* Map parsing prototypes (public) */
int		is_map_line(char *line);
int		count_map_lines(char **lines, int start);
int		check_no_content_after_map(char **lines, int map_start, int map_count);
int		get_max_width(char **grid);
int		get_map_max_width(char **lines, int start, int count);
char	*copy_map_line(char *line, int max);
char	**extract_map(char **lines, int start, int count);
int		parse_textures(t_map *map, char **lines, int *map_start);
int		parse_colors(t_map *map, char **lines);
int		open_file(char *filename);
char	**read_file_lines(char *filename, int *total_lines);
void	free_all_lines(char **lines, int count);
t_map	*parse_map(char *filename);

/*---------------------------------------------------------*/
/* Map validation */
int     check_chars(t_map *map);
int     find_player(t_map *map, int *px, int *py, char *dir);
int     check_cell_edges(char **grid, int y, int x, int height);
int     check_walls(t_map *map);
int     check_map_closed(t_map *map, int px, int py);
int     validate_map(t_map *map);

/* helper type used by map closure check */
typedef struct s_dfs
{
	int     w;
	int     h;
	char    *vis;
	t_map   *map;
}   t_dfs;

/*---------------------------------------------------------*/
/* render_frame.c */
void    render_frame(t_game *game);

/* mlx_setup.c */
int     init_mlx(t_game *game);
void    setup_hooks(t_game *game);
int     game_loop(t_game *game);

/* helpers */
void    print_debug_info_first_frame(t_game *game);
void    print_center_ray_debug(t_ray *ray);

#endif
