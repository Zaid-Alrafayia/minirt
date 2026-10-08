/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalghamd <jalghamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 16:33:34 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/09/29 19:43:55 by jalghamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static int	check_args(int ac, char **av)
{
	if (ac != 2)
	{
		ft_putstr_fd("Error\nmust be -> ./miniRT <scene.rt>\n", 2);
		return (0);
	}
	if (!check_extension(av[1]))
	{
		ft_putstr_fd("Error\nfile extension must be a .rt file\n", 2);
		return (0);
	}
	if (!check_fvalidity(av[1]))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_app	*app;

	if (!check_args(ac, av))
		return (1);
	app = malloc(sizeof(t_app));
	if (!app)
	{
		ft_putstr_fd("Error\nmemory allocation failed\n", 2);
		return (1);
	}
	ft_bzero(app, sizeof(t_app));
	if (!read_fscene(av[1], app))
	{
		free_scene(&app->scene);
		free(app);
		return (1);
	}
	init_window(app);
	return (0);
}
