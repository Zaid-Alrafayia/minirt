/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   veccross.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalghamd <jalghamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 21:29:50 by jalghamd          #+#    #+#             */
/*   Updated: 2026/10/03 21:31:50 by jalghamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mathlib.h"

t_vec3	veccross(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	res;

	res.x = vec1.y * vec2.z - vec1.z * vec2.y;
	res.y = vec1.z * vec2.x - vec1.x * vec2.z;
	res.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (res);
}
