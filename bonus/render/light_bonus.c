/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 23:49:43 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/10/30 23:50:49 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

double	get_specular(t_vec3 l, t_vec3 n, t_vec3 ray_dir, double brightness)
{
	t_vec3 reflect_dir;
	t_vec3 view_dir;
	double spec_angle;

	view_dir = normvec(vecscale(ray_dir, -1.0));
	reflect_dir = vecsub(vecscale(n, 2.0 * dotprod(n, l)), l);
	spec_angle = fmax(0.0, dotprod(reflect_dir, view_dir));
	return (0.5 * brightness * pow(spec_angle, 64.0));
}