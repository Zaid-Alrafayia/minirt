/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 16:14:34 by jalghamd          #+#    #+#             */
/*   Updated: 2026/10/01 02:21:34 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

int	init_sphere(char **parts, t_app *app)
{
	t_object	*obj;
	t_sphere	*sp;
	t_color		color;

	color = parse_color(parts[3]);
	if (!is_valid_color(color))
		return (0);
	obj = malloc(sizeof(t_object));
	if (!obj)
		return (0);
	sp = malloc(sizeof(t_sphere));
	if (!sp)
	{
		free(obj);
		return (0);
	}
	sp->center = parse_vec3(parts[1]);
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

	color = parse_color(parts[3]);
	if (!is_valid_color(color))
		return (0);
	obj = malloc(sizeof(t_object));
	if (!obj)
		return (0);
	pl = malloc(sizeof(t_plane));
	if (!pl)
	{
		free(obj);
		return (0);
	}
	pl->point = parse_vec3(parts[1]);
	pl->normal = normvec(parse_vec3(parts[2]));
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

	color = parse_color(parts[5]);
	if (!is_valid_color(color))
		return (0);
	obj = malloc(sizeof(t_object));
	if (!obj)
		return (0);
	cy = malloc(sizeof(t_cylinder));
	if (!cy)
	{
		free(obj);
		return (0);
	}
	cy->center = parse_vec3(parts[1]);
	cy->axis = normvec(parse_vec3(parts[2]));
	cy->diameter = ft_atof(parts[3]);
	cy->height = ft_atof(parts[4]);
	obj->type = OBJ_CYLINDER;
	obj->color = color;
	obj->data = cy;
	ft_lstadd_back(&app->scene.objects, ft_lstnew(obj));
	return (1);
}
