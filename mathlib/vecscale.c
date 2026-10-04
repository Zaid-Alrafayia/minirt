/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecscale.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalghamd <jalghamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 21:31:59 by jalghamd          #+#    #+#             */
/*   Updated: 2026/10/03 21:33:33 by jalghamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mathlib.h"

t_vec3	vecscale(t_vec3 vec, double scalar)
{
	t_vec3	res;

	res.x = vec.x * scalar;
	res.y = vec.y * scalar;
	res.z = vec.z * scalar;
	return (res);
}
