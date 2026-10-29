/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_helper_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:51:14 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/10/29 14:29:56 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

t_vec3	get_cylinder_normal(t_hit *hit, t_cylinder *cy)
{
	double	m;

	m = dotprod(vecsub(hit->point, cy->center), cy->axis);
	if (fabs(fabs(m) - cy->height / 2.0) < EPSILON)
		return (cy->axis);
	return (normvec(vecsub(hit->point, vecadd(cy->center, vecscale(cy->axis,
						m)))));
}
