/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 16:14:34 by jalghamd          #+#    #+#             */
/*   Updated: 2026/10/07 11:45:18 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

int	init_sphere(char **parts, t_app *app)
{
	t_object	*obj;
	t_sphere	*sp;
	t_color		color;

	if (arrstr_len(parts) != 4)
		return (-3);
	color = parse_color(parts[3]);
	if (!is_valid_color(color) || !is_num(parts[2]) || ft_atof(parts[2]) <= 0)
		return (0);
	obj = malloc(sizeof(t_object));
	if (!obj)
		return (0);
	sp = malloc(sizeof(t_sphere));
	if (!sp || parse_vec3(parts[1], &sp->center))
	{
		free(obj);
		return (0);
	}
	sp->diameter = ft_atof(parts[2]);
	obj->type = OBJ_SPHERE;
	obj->color = color;
	obj->data = sp;
	ft_lstadd_back(&app->scene.objects, ft_lstnew(obj));
	return (1);
}

int	init_plane(char **parts, t_app *app)
{
	t_object	*obj;
	t_plane		*pl;
	t_color		color;

	if (arrstr_len(parts) != 4)
		return (-3);
	color = parse_color(parts[3]);
	if (!is_valid_color(color))
		return (0);
	obj = malloc(sizeof(t_object));
	if (!obj)
		return (0);
	pl = malloc(sizeof(t_plane));
	if (!pl || parse_vec3(parts[1], &pl->point) || parse_vec3(parts[2],
			&pl->normal) || is_zero_vec(pl->normal))
	{
		free(obj);
		return (0);
	}
	pl->normal = normvec(pl->normal);
	obj->type = OBJ_PLANE;
	obj->color = color;
	obj->data = pl;
	ft_lstadd_back(&app->scene.objects, ft_lstnew(obj));
	return (1);
}

int	init_cylinder(char **parts, t_app *app)
{
	t_object	*obj;
	t_cylinder	*cy;
	t_color		color;
	t_list		*node;

	if (arrstr_len(parts) != 6)
		return (-3);
	color = parse_color(parts[5]);
	if (!is_valid_color(color) || !is_num(parts[3]) || !is_num(parts[4]))
		return (0);
	obj = malloc(sizeof(t_object));
	if (!obj)
		return (0);
	cy = malloc(sizeof(t_cylinder));
	if (!cy || parse_vec3(parts[1], &cy->center) || parse_vec3(parts[2],
			&cy->axis) || is_zero_vec(cy->axis))
	{
		free(obj);
		return (0);
	}
	cy->diameter = ft_atof(parts[3]);
	cy->height = ft_atof(parts[4]);
	cy->axis = normvec(cy->axis);
	obj->type = OBJ_CYLINDER;
	obj->color = color;
	obj->data = cy;
	node = ft_lstnew(obj);
	if (cy->diameter <= 0 || cy->height <= 0 || !node)
	{
		free(obj);
		free(cy);
		return (0);
	}
	ft_lstadd_back(&app->scene.objects, node);
	return (1);
}
