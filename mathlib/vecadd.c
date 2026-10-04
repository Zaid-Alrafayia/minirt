/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecadd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalghamd <jalghamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 01:38:43 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/10/03 21:35:32 by jalghamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mathlib.h"

t_vec3	vecadd(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	resvec;

	resvec.x = vec1.x + vec2.x;
	resvec.y = vec1.y + vec2.y;
	resvec.z = vec1.z + vec2.z;
	return (resvec);
}
