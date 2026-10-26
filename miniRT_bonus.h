/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 16:08:58 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/09/28 16:18:19 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H
# define WIDTH 960
# define HEIGHT 540
# define EPSILON 0.0001

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# include "42_libft/libft.h"
# include "miniRT_structs_bonus.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <float.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

void	init_window(t_app *app);
void	free_object(void *content);
void	free_scene(t_scene *scene);
int		check_fvalidity(char *file);
int		check_extension(char *file);
void	free_split(char **parts);
int		read_fscene(char *file, t_app *app);
double	ft_atof(char *str);
int		parse_vec3(char *str, t_vec3 *vec);
t_color	parse_color(char *str);
int		init_ambient(char **parts, t_app *app);
int		init_camera(char **parts, t_app *app);
int		init_light(char **parts, t_app *app);
int		init_sphere(char **parts, t_app *app);
int		init_plane(char **parts, t_app *app);
int		init_cylinder(char **parts, t_app *app);
int		is_valid_color(t_color c);
void	clean_gnl(int fd);
int		check_lca(int fd, t_app *app, char *line);
void	camera_basis(t_camera *cam);
t_ray	camera_ray(t_camera *cam, double x, double y);
int		pack_color(t_color color);
void	put_pixel(t_img *img, int x, int y, int color);
void	render_scene(t_app *app);
int		find_closest_hit(t_ray ray, t_scene *scene, t_hit *hit);
t_color	trace_ray(t_ray ray, t_scene *scene);
int		intersect_sphere(t_ray ray, t_sphere *sphere, t_hit *hit);
int		intersect_plane(t_ray ray, t_plane *plane, t_hit *hit);
int		intersect_cylinder(t_ray ray, t_cylinder *cy, t_hit *hit);
void	check_lights(t_ray ray, t_hit *hit, t_scene *scene);
int		is_valid_normal(t_vec3 v);

double	vecmag(const t_vec3 vec);
int		is_zero_vec(t_vec3 vec);
t_vec3	vecadd(t_vec3 vec1, t_vec3 vec2);
t_vec3	vecsub(t_vec3 vec1, t_vec3 vec2);
t_vec3	normvec(t_vec3 vec);
double	dotprod(t_vec3 vec1, t_vec3 vec2);
t_vec3	vecscale(t_vec3 vec, double scalar);
t_vec3	veccross(t_vec3 vec1, t_vec3 vec2);
double	veclen(t_vec3 v);

#endif
