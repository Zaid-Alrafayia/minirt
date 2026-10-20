/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalghamd <jalghamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 16:14:30 by jalghamd          #+#    #+#             */
/*   Updated: 2026/10/20 22:41:48 by jalghamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

static int	count_commas(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

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

	if (!str || count_commas(str) != 2)
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

	if (!str || count_commas(str) != 2)
		return ((t_color){-1.0, -1.0, -1.0});
	color.r = -1.0;
	color.g = -1.0;
	color.b = -1.0;
	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3]
		|| !is_int(parts[0]) || !is_int(parts[1]) || !is_int(parts[2]))
	{
		free_split(parts);
		return (color);
	}
	color.r = ft_atof(parts[0]) / 255.0;
	color.g = ft_atof(parts[1]) / 255.0;
	color.b = ft_atof(parts[2]) / 255.0;
	free_split(parts);
	return (color);
}
