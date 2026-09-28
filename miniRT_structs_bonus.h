/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_structs_bonus.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 16:07:47 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/09/28 16:07:51 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_STRUCTS_BONUS_H
# define MINIRT_STRUCTS_BONUS_H

typedef struct s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

typedef struct s_color
{
	double		r;
	double		g;
	double		b;
}				t_color;

typedef struct s_ray
{
	t_vec3		origin;
	t_vec3		dir;
}				t_ray;

typedef struct s_img
{
	void		*img_ptr;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_material
{
	double		specular;
	double		shininess;
	int			is_checkered;
	t_color		color2;
	int			has_bump;
	t_img		bump_map;
}				t_material;

typedef enum e_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_CONE
}				t_type;

typedef struct s_sphere
{
	t_vec3		center;
	double		diameter;
	double		radius;
	double		radius_sq;
}				t_sphere;

typedef struct s_plane
{
	t_vec3		point;
	t_vec3		normal;
}				t_plane;

typedef struct s_cylinder
{
	t_vec3		center;
	t_vec3		axis;
	double		diameter;
	double		radius;
	double		radius_sq;
	double		height;
}				t_cylinder;

typedef struct s_cone
{
	t_vec3		tip;
	t_vec3		axis;
	double		angle;
	double		height;
}				t_cone;

typedef struct s_object
{
	t_type		type;
	void		*data;
	t_color		color;
	t_material	mat;
}				t_object;

typedef struct s_hit
{
	double		t;
	t_vec3		point;
	t_vec3		normal;
	t_color		color;
	t_material	mat;
	t_object	*obj;
}				t_hit;

typedef struct s_camera
{
	t_vec3		pos;
	t_vec3		dir;
	double		fov;
	double		scale;
	double		aspect_ratio;
	t_vec3		right_vec;
	t_vec3		up_vec;
	t_vec3		forward_vec;
}				t_camera;

typedef struct s_ambient
{
	double		ratio;
	t_color		color;
}				t_ambient;

typedef struct s_light
{
	t_vec3		pos;
	double		brightness;
	t_color		color;
}				t_light;

typedef struct s_scene
{
	t_ambient	amb_light;
	t_camera	cam;
	t_list		*lights;
	t_list		*objects;
}				t_scene;

typedef struct s_app
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_scene		scene;
}				t_app;

#endif
