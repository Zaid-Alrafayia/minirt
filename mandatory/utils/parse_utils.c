/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 16:14:30 by jalghamd          #+#    #+#             */
/*   Updated: 2026/10/05 02:30:27 by zaalrafa         ###   ########.fr       */
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

int	parse_vec3(char *str, t_vec3 *vec)
{
	char	**parts;

	if (!str)
		return (1);
	parts = ft_split(str, ',');
	if (!parts)
		return (1);
	if (!parts[0] || !parts[1] || !parts[2] || parts[3] || !is_num(parts[0])
		|| !is_num(parts[1]) || !is_num(parts[2]))
	{
		free_split(parts);
		return (1);
	}
	vec->x = ft_atof(parts[0]);
	vec->y = ft_atof(parts[1]);
	vec->z = ft_atof(parts[2]);
	free_split(parts);
	return (0);
}

t_color	parse_color(char *str)
{
	t_color	color;
	char	**parts;

	color.r = -1;
	color.g = -1;
	color.b = -1;
	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3]
		|| !is_int(parts[0]) || !is_int(parts[1]) || !is_int(parts[2]))
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
