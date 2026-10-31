/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalghamd <jalghamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 23:49:43 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/11/01 00:40:29 by jalghamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

double	get_specular(t_vec3 l, t_vec3 n, t_vec3 ray_dir, double brightness)
{
	t_vec3	reflect_dir;
	t_vec3	view_dir;
	double	spec_angle;

	view_dir = normvec(vecscale(ray_dir, -1.0));
	reflect_dir = vecsub(vecscale(n, 2.0 * dotprod(n, l)), l);
	spec_angle = fmax(0.0, dotprod(reflect_dir, view_dir));
	return (0.5 * brightness * pow(spec_angle, 64.0));
}
