/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalghamd <jalghamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 16:33:34 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/09/28 21:37:54 by jalghamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	main(int ac, char **av)
{
	t_app	*app;

	if (ac != 2)
	{
		ft_putstr_fd("Error\n must be -> ./miniRT <scene.rt>\n", 2);
		return (1);
	}
	if (!check_extension(av[1]))
	{
		ft_putstr_fd("Error\nIncorrect file extension must be a .rt file\n", 2);
		return (1);
	}
	if (!check_fvalidity(av[1]))
		return (1);
	app = malloc(sizeof(t_app));
	if (!app)
	{
		ft_putstr_fd("Error\nMemory allocation failed\n", 2);
		return (1);
	}
	init_window(app);
	return (0);
}
