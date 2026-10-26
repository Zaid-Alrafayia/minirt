/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objs_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 16:14:34 by jalghamd          #+#    #+#             */
/*   Updated: 2026/10/25 07:12:00 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

static int	add_object(t_object *obj, t_app *app)
{
	t_list	*node;

	node = ft_lstnew(obj);
	if (!node)
	{
		free_object(obj);
		return (0);
	}
	ft_lstadd_back(&app->scene.objects, node);
	return (1);
}

int	init_sphere(char **parts, t_app *app)
{
	t_object	*obj;
	t_sphere	*sp;
	t_color		color;

	if (!(arrstr_len(parts) >= 4 && arrstr_len(parts) <= 6))
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
		free(sp);
		free(obj);
		return (0);
	}
	sp->diameter = ft_atof(parts[2]);
	if (arrstr_len(parts) == 5 || arrstr_len(parts) == 6)
		sp->texture_map = ft_strdup(parts[4]);
	if (arrstr_len(parts) == 6)
		sp->bump_map = ft_strdup(parts[5]);
	obj->type = OBJ_SPHERE;
	obj->color = color;
	obj->data = sp;
	return (add_object(obj, app));
}

int	init_plane(char **parts, t_app *app)
{
	t_object	*obj;
	t_plane		*pl;
	t_color		color;

	if (!(arrstr_len(parts) >= 4 && arrstr_len(parts) <= 6))
		return (-3);
	color = parse_color(parts[3]);
	if (!is_valid_color(color))
		return (0);
	obj = malloc(sizeof(t_object));
	if (!obj)
		return (0);
	pl = malloc(sizeof(t_plane));
	if (!pl || parse_vec3(parts[1], &pl->point) || parse_vec3(parts[2],
			&pl->normal) || !is_valid_normal(pl->normal))
	{
		free(pl);
		free(obj);
		return (0);
	}
	if (arrstr_len(parts) == 5 || arrstr_len(parts) == 6)
		pl->texture_map = ft_strdup(parts[4]);
	if (arrstr_len(parts) == 6)
		pl->bump_map = ft_strdup(parts[5]);
	pl->normal = normvec(pl->normal);
	obj->type = OBJ_PLANE;
	obj->color = color;
	obj->data = pl;
	return (add_object(obj, app));
}
