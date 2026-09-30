/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathlib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 20:57:33 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/10/01 02:39:18 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHLIB_H
# define MATHLIB_H
# include "../miniRT_structs.h"
# include <math.h>
double	norm(double value, double max, double min, double a, double b);
double	vecmag(const t_vec3 vec);
t_vec3	vecadd(t_vec3 vec1, t_vec3 vec2);
t_vec3	vecsub(t_vec3 vec1, t_vec3 vec2);
t_vec3	normvec(t_vec3 vec);
double	dotprod(t_vec3 vec1, t_vec3 vec2);

#endif