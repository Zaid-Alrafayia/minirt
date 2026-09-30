/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normvec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 02:04:03 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/10/01 02:41:12 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mathlib.h"

t_vec3	normvec(t_vec3 vec)
{
	t_vec3 res;
	double magnitude = vecmag(vec);
	if (magnitude == 0)
		return (vec);
	res.x = vec.x / magnitude;
	res.y = vec.y / magnitude;
	res.z = vec.z / magnitude;
	return (res);
}