/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 00:19:49 by jalghamd          #+#    #+#             */
/*   Updated: 2026/10/18 23:20:34 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

static int	intersect_obj(t_ray ray, t_object *obj, t_hit *hit)
{
	int	is_hit;

	is_hit = 0;
	if (!obj || !obj->data)
		return (0);
	if (obj->type == OBJ_SPHERE)
		is_hit = intersect_sphere(ray, obj->data, hit);
	else if (obj->type == OBJ_PLANE)
		is_hit = intersect_plane(ray, obj->data, hit);
	else if (obj->type == OBJ_CYLINDER)
		is_hit = intersect_cylinder(ray, obj->data, hit);
	if (is_hit)
	{
		hit->color = obj->color;
		hit->point = vecadd(ray.origin, vecscale(ray.dir, hit->t));
		hit->obj = obj;
	}
	return (is_hit);
}

int	find_closest_hit(t_ray ray, t_scene *scene, t_hit *hit)
{
	t_list	*curr;
	t_hit	tmp_hit;
	int		hit_found;

	hit_found = 0;
	hit->t = DBL_MAX;
	curr = scene->objects;
	while (curr)
	{
		if (intersect_obj(ray, (t_object *)curr->content, &tmp_hit))
		{
			if (tmp_hit.t > EPSILON && tmp_hit.t < hit->t)
			{
				*hit = tmp_hit;
				hit_found = 1;
			}
		}
		curr = curr->next;
	}
	return (hit_found);
}

t_color	trace_ray(t_ray ray, t_scene *scene)
{
	t_hit	hit;

	if (find_closest_hit(ray, scene, &hit))
	{
		check_lights(ray, &hit, scene);
		return (hit.color);
	}
	return ((t_color){0.0, 0.0, 0.0});
}

void	render_scene(t_app *app)
{
	int		x;
	int		y;
	t_ray	ray;
	int		color;

	camera_basis(&app->scene.cam);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = camera_ray(&app->scene.cam, (double)x, (double)y);
			color = pack_color(trace_ray(ray, &app->scene));
			put_pixel(&app->img, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(app->mlx, app->win, app->img.img_ptr, 0, 0);
}
