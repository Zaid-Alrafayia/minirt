/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalghamd <jalghamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 16:14:30 by jalghamd          #+#    #+#             */
/*   Updated: 2026/09/29 19:43:59 by jalghamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

double	ft_atof(char *str)
{
	double	res;
	double	div;
	int		sign;

	res = 0.0;
	div = 1.0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		res = res * 10.0 + (*str++ - '0');
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			res = res * 10.0 + (*str++ - '0');
			div *= 10.0;
		}
	}
	return ((sign * res) / div);
}

t_vec3	parse_vec3(char *str)
{
	t_vec3	vec;
	char	**parts;

	vec.x = 0;
	vec.y = 0;
	vec.z = 0;
	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2])
	{
		free_split(parts);
		return (vec);
	}
	vec.x = ft_atof(parts[0]);
	vec.y = ft_atof(parts[1]);
	vec.z = ft_atof(parts[2]);
	free_split(parts);
	return (vec);
}

t_color	parse_color(char *str)
{
	t_color		color;
	char		**parts;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2])
	{
		free_split(parts);
		return (color);
	}
	color.r = ft_atof(parts[0]);
	color.g = ft_atof(parts[1]);
	color.b = ft_atof(parts[2]);
	free_split(parts);
	return (color);
}

int	is_valid_color(t_color c)
{
	if (c.r < 0 || c.r > 255 || c.g < 0 || c.g > 255 || c.b < 0 || c.b > 255)
		return (0);
	return (1);
}
