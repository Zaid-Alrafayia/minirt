/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalghamd <jalghamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 23:45:21 by jalghamd          #+#    #+#             */
/*   Updated: 2026/11/01 00:00:51 by jalghamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

void	get_object_uv(t_hit *hit, double *u, double *v)
{
	if (hit->obj->type == OBJ_SPHERE)
		get_sphere_uv(hit, u, v);
	else if (hit->obj->type == OBJ_PLANE)
		get_plane_uv(hit, u, v);
	else if (hit->obj->type == OBJ_CYLINDER)
		get_cylinder_uv(hit, u, v);
	else if (hit->obj->type == OBJ_CONE)
		get_cone_uv(hit, u, v);
	else
	{
		*u = 0.0;
		*v = 0.0;
	}
}

t_color	get_checker_color(t_hit *hit)
{
	double	u;
	double	v;
	double	scale;
	int		check;

	scale = 16.0;
	if (hit->obj->type == OBJ_PLANE)
		scale = 0.5;
	get_object_uv(hit, &u, &v);
	check = (int)(floor(u * scale)) + (int)(floor(v * scale));
	if (((check % 2) + 2) % 2 == 0)
		return (hit->obj->color);
	return ((t_color){1.0, 1.0, 1.0});
}
