/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalghamd <jalghamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 20:29:37 by jalghamd          #+#    #+#             */
/*   Updated: 2026/10/08 00:45:05 by jalghamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

static t_vec3	get_world_up(t_vec3 forward)
{
	if (fabs(forward.y) > 1.0 - EPSILON)
		return ((t_vec3){0.0, 0.0, 1.0});
	return ((t_vec3){0.0, 1.0, 0.0});
}

void	camera_basis(t_camera *cam)
{
	t_vec3	world_up;

	if (!cam)
		return ;
	cam->forward_vec = normvec(cam->dir);
	world_up = get_world_up(cam->forward_vec);
	cam->right_vec = normvec(veccross(world_up, cam->forward_vec));
	cam->up_vec = normvec(veccross(cam->forward_vec, cam->right_vec));
	cam->fov = cam->fov * (M_PI / 180.0);
}

t_ray	camera_ray(t_camera *cam, double x, double y)
{
	t_ray	ray;
	t_vec3	dir;
	double	scale;
	double	u;
	double	v;

	scale = tan(cam->fov / 2.0);
	u = ((2.0 * (x + 0.5) / WIDTH) - 1.0) * scale;
	v = (1.0 - (2.0 * (y + 0.5) / HEIGHT)) * scale * ((double)HEIGHT / WIDTH);
	dir.x = cam->forward_vec.x + (u * cam->right_vec.x) + (v * cam->up_vec.x);
	dir.y = cam->forward_vec.y + (u * cam->right_vec.y) + (v * cam->up_vec.y);
	dir.z = cam->forward_vec.z + (u * cam->right_vec.z) + (v * cam->up_vec.z);
	ray.origin = cam->pos;
	ray.dir = normvec(dir);
	return (ray);
}
