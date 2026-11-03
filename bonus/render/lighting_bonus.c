/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 19:29:03 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/11/04 01:38:14 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

t_vec3	get_normal(t_ray ray, t_hit *hit)
{
	t_vec3	n;
	t_cone	*co;
	double	m;

	n = (t_vec3){0, 0, 0};
	if (hit->obj->type == OBJ_SPHERE)
		n = normvec(vecsub(hit->point, ((t_sphere *)hit->obj->data)->center));
	else if (hit->obj->type == OBJ_PLANE)
		n = ((t_plane *)hit->obj->data)->normal;
	else if (hit->obj->type == OBJ_CYLINDER)
		n = get_cylinder_normal(hit, (t_cylinder *)hit->obj->data);
	else if (hit->obj->type == OBJ_CONE)
	{
		co = (t_cone *)hit->obj->data;
		m = dotprod(vecsub(hit->point, co->center), co->axis);
		if (fabs(m - co->height) < EPSILON)
			n = co->axis;
		else
			n = normvec(vecsub(vecsub(hit->point, co->center),
						vecscale(co->axis, m * (1.0 + co->k_sq))));
	}
	if (dotprod(ray.dir, n) > 0)
		n = vecscale(n, -1.0);
	return (n);
}

static int	in_shadow(t_hit *hit, t_vec3 n, t_light *light, t_scene *scene)
{
	t_ray	shadow_ray;
	t_hit	shadow_hit;
	double	light_dist;

	shadow_ray.origin = vecadd(hit->point, vecscale(n, EPSILON));
	shadow_ray.dir = normvec(vecsub(light->pos, hit->point));
	light_dist = veclen(vecsub(light->pos, hit->point));
	if (find_closest_hit(shadow_ray, scene, &shadow_hit))
	{
		if (shadow_hit.t < light_dist)
			return (1);
	}
	return (0);
}

static void	apply_light(t_color *light_cont, t_hit *hit, t_light *light,
		t_scene *scene)
{
	t_vec3	l;
	double	dot_nl;
	t_vec3	r;
	double	specular;

	l = normvec(vecsub(light->pos, hit->point));
	dot_nl = dotprod(hit->normal, l);
	specular = 0.0;
	if (dot_nl > 0)
	{
		r = vecsub(vecscale(hit->normal, 2 * dot_nl), l);
		specular = pow(fmax(0, dotprod(r, hit->view_v)), 32);
	}
	if (!in_shadow(hit, hit->normal, light, scene))
	{
		light_cont->r += (hit->color.r * fmax(0, dot_nl) + specular)
			* light->brightness * light->color.r;
		light_cont->g += (hit->color.g * fmax(0, dot_nl) + specular)
			* light->brightness * light->color.g;
		light_cont->b += (hit->color.b * fmax(0, dot_nl) + specular)
			* light->brightness * light->color.b;
	}
}

static void	clamp_light(t_color *light_cont)
{
	if (light_cont->r > 1.0)
		light_cont->r = 1.0;
	if (light_cont->g > 1.0)
		light_cont->g = 1.0;
	if (light_cont->b > 1.0)
		light_cont->b = 1.0;
}

void	check_lights(t_ray ray, t_hit *hit, t_scene *scene)
{
	t_list	*curr;
	t_color	light_cont;

	if (hit->obj->tex.img)
		hit->color = get_texture_color(hit, &hit->obj->tex);
	else if (hit->obj->is_checker)
		hit->color = get_checker_color(hit);
	hit->normal = get_normal(ray, hit);
	if (hit->obj->bump.img)
		hit->normal = bump_mapping(hit, &hit->obj->bump);
	hit->view_v = normvec(vecscale(ray.dir, -1.0));
	curr = scene->lights;
	light_cont.r = hit->color.r * scene->amb_light.ratio
		* scene->amb_light.color.r;
	light_cont.g = hit->color.g * scene->amb_light.ratio
		* scene->amb_light.color.g;
	light_cont.b = hit->color.b * scene->amb_light.ratio
		* scene->amb_light.color.b;
	while (curr)
	{
		apply_light(&light_cont, hit, (t_light *)curr->content, scene);
		curr = curr->next;
	}
	clamp_light(&light_cont);
	hit->color = light_cont;
}
