/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalghamd <jalghamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 22:25:17 by jalghamd          #+#    #+#             */
/*   Updated: 2026/10/20 22:47:07 by jalghamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

int	is_valid_normal(t_vec3 v)
{
	if (is_zero_vec(v))
		return (0);
	if (v.x < -1.0 || v.x > 1.0 || v.y < -1.0 || v.y > 1.0
		|| v.z < -1.0 || v.z > 1.0)
		return (0);
	return (1);
}

int	is_valid_color(t_color c)
{
	if (c.r < 0.0 || c.r > 1.0 || c.g < 0.0 || c.g > 1.0 || c.b < 0.0
		|| c.b > 1.0)
		return (0);
	return (1);
}
