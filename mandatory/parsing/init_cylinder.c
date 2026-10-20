/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalghamd <jalghamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 00:38:27 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/10/20 22:45:28 by jalghamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

static int	init_cylinder_data(char **parts, t_cylinder **cy)
{
	*cy = malloc(sizeof(t_cylinder));
	if (!*cy)
		return (0);
	if (parse_vec3(parts[1], &(*cy)->center) || parse_vec3(parts[2],
			&(*cy)->axis) || !is_valid_normal((*cy)->axis))
	{
		free(*cy);
		return (0);
	}
	(*cy)->diameter = ft_atof(parts[3]);
	(*cy)->height = ft_atof(parts[4]);
	(*cy)->axis = normvec((*cy)->axis);
	if ((*cy)->diameter <= 0 || (*cy)->height <= 0)
	{
		free(*cy);
		return (0);
	}
	return (1);
}

static int	add_cylinder(t_cylinder *cy, t_color color, t_app *app)
{
	t_object	*obj;
	t_list		*node;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (free(cy), 0);
	obj->type = OBJ_CYLINDER;
	obj->color = color;
	obj->data = cy;
	node = ft_lstnew(obj);
	if (!node)
		return (free_object(obj), 0);
	ft_lstadd_back(&app->scene.objects, node);
	return (1);
}

int	init_cylinder(char **parts, t_app *app)
{
	t_cylinder	*cy;
	t_color		color;

	if (arrstr_len(parts) != 6)
		return (-3);
	color = parse_color(parts[5]);
	if (!is_valid_color(color) || !is_num(parts[3]) || !is_num(parts[4]))
		return (0);
	if (!init_cylinder_data(parts, &cy))
		return (0);
	return (add_cylinder(cy, color, app));
}
