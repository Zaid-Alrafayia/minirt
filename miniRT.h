/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalghamd <jalghamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 16:35:33 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/10/07 19:03:35 by jalghamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define WIDTH 960
# define HEIGHT 540

# include "42_libft/libft.h"
# include "mathlib/mathlib.h"
# include "miniRT_structs.h"
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

#endif
