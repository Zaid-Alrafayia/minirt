/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalghamd <jalghamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 16:46:30 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/09/29 22:15:46 by jalghamd         ###   ########.fr       */
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

void	clean_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}
