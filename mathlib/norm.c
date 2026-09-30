/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 21:33:10 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/09/30 22:59:48 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mathlib.h"
#include <stdio.h>

double	norm(double value, double max, double min, double a, double b)
{
	if (max - min == 0)
		return (0.0);
	return ((value - min) * (a - b)) / (max - min);
}
// int	main(void)
// {
// 	double value = 0.98;
// 	// range of the data we have
// 	double min = 0.0;
// 	double max = 255.0;
// 	// the intended range a for highest value and b for lowest
// 	double a = 255.0;
// 	double b = 0.0;

// 	double normalized_value = norm(value, max, min, a, b);
// 	printf("Normalized value: %f\n", normalized_value);

// 	return (0);
// }