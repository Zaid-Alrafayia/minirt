/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 16:46:30 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/09/28 16:47:29 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../miniRT.h"

void	free_object(void *content)
{
	t_object	*obj;

	obj = (t_object *)content;
	if (!obj)
		return ;
	if (obj->data)
		free(obj->data);
	free(obj);
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->objects)
		ft_lstclear(&scene->objects, free_object);
	if (scene->lights)
		ft_lstclear(&scene->lights, free);
}
